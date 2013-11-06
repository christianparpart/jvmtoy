#include "JvmEnv.h"
#include "Class.h"
#include "ConstantPool.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

JvmEnv::JvmEnv()
{
	classpaths_.push_back(".");
}

JvmEnv::~JvmEnv()
{
}

void JvmEnv::addClassPath(const std::string& path)
{
	classpaths_.push_back(path);
}

/**
 * Returns a class object by given name, possibly loading on demand.
 *
 * @param className the fully qualified class name, i.e. java.lang.String
 * @return pointer to the requested class or \p nullptr if not found.
 */
Class* JvmEnv::getClass(const std::string& className)
{
	auto i = classes_.find(className);
	if (i != classes_.end()) {
		printf("JvmEnv.getClass(%s) -> cached\n", className.c_str());
		return i->second;
	}

	std::string normalizedClassName = className;
	for (int i = 0; i < normalizedClassName.size(); ++i)
		if (normalizedClassName[i] == '.')
			normalizedClassName[i] = '/';

	for (auto path: classpaths_) {
		path += "/";
		path += normalizedClassName;
		path += ".class";

		//printf("getClass(%s): try '%s'\n", className.c_str(), path.c_str());
		struct stat st;
		if (stat(path.c_str(), &st) < 0)
			continue;

		Class* c = new Class(this);
		printf("Loading classfile: '%s' for %s\n", path.c_str(), className.c_str());

		classes_[className] = c;

		if (!c->load(path)) {
			printf("Loading classfile '%s' failed.\n", c->name().c_str());
			classes_.erase(classes_.find(c->name()));
			delete c;
			continue;
		}
		return c;
	}

	return nullptr;
}
