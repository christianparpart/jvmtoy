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

Class* JvmEnv::getClass(const std::string& className)
{
	auto i = classes_.find(className);
	if (i != classes_.end())
		return i->second;

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

		if (Class* c = Class::load(path.c_str())) {
			classes_[className] = c;
			return c;
		}
	}

	return nullptr;
}
