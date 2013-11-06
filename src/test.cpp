#include "JvmEnv.h"
#include "Class.h"
#include "ConstantPool.h"

int main(int argc, const char* argv[])
{
	JvmEnv jenv;
	jenv.addClassPath("./tests");
	jenv.addClassPath("/home/trapni/projects/jvmtoy/classpath-rt");

	std::string className = argc == 2 ? argv[1] : "Test";
	Class* c = jenv.getClass(className);
	if (!c) {
		fprintf(stderr, "Could not find class '%s'.\n", className.c_str());
		return 1;
	}

	c->dump();

	Method* method = c->findMethod("main");
	int errors = 0;
	if (!method) {
		fprintf(stderr, "Could not find method '%s' in %s.\n", "main", c->name().c_str());
		++errors;
	} else {
		if (!(method->flags() & MethodFlags::Public)) { printf("main: must be public\n"); ++errors; }
		if (!(method->flags() & MethodFlags::Static)) { printf("main: must be static\n"); ++errors; }
		if (method->signature() != "([Ljava/lang/String;)V") { printf("main: invalid signature\n"); ++errors; }
	}
	if (!errors) {
		printf("entry method found\n");
	}

	return 0;
}
