#include "ConstantPool.h"
#include "JvmEnv.h"

bool ConstantClass::resolve(JvmEnv* env)
{
	if (resolvedClass)
		return true;

	resolvedClass = env->getClass(name->c_str());
	return true;
}
