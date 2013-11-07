#include "JvmEnv.h"
#include "Class.h"
#include "ConstantPool.h"
#include "VMClassLoader.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

JvmEnv::JvmEnv()
{
	classLoader_ = new VMClassLoader();
	classpaths_.push_back(".");
}

JvmEnv::~JvmEnv()
{
}

void JvmEnv::addClassPath(const std::string& path)
{
	classLoader_->addClassPath(path);
}

/**
 * Returns a class object by given name, possibly loading on demand.
 *
 * @param className the fully qualified class name, i.e. java.lang.String
 * @return pointer to the requested class or \p nullptr if not found.
 */
Class* JvmEnv::getClass(const std::string& className)
{
	return classLoader_->findClass(className.c_str());
}
