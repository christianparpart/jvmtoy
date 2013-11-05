#include "JvmEnv.h"
#include "Class.h"
#include "ConstantPool.h"

int main(int argc, const char* argv[])
{
	JvmEnv jenv;
	jenv.addClassPath("./tests");
	jenv.addClassPath("/home/trapni/projects/jvmtoy/classpath-rt");

	std::string className = argc == 2 ? argv[1] : "Test";
	if (Class* c = jenv.getClass(className)) {
		c->dump();
	} else {
		fprintf(stderr, "Could not find class '%s'.\n", className.c_str());
	}

//	Class* c = Class::load(argc == 2 ? argv[1] : "tests/Test.class");
//	delete c;

	return 0;
}
