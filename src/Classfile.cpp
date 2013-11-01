#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <vector>

enum class ConstantTag {
	Class = 7,
	Fieldref = 9,
	Methodref = 10,
	InterfaceMethodref = 11,
	String = 8,
	Integer = 3,
	Float = 4,
	Long = 5,
	Double = 6,
	NameAndType = 12,
	Utf8 = 1,
	MethodHandle = 15,
	MethodType = 16,
	InvokeDynamic = 18,
};

class Constant {
};

class ConstantPool {
	std::vector<Constant*> pool;

public:
	ConstantPool() {
	}

	~ConstantPool() {
	}

	void resize(size_t size) {
		pool.resize(size);
	}

	Constant* operator[](size_t id) const { return pool[id]; }
};

class Classfile {
public:
	ConstantPool constantPool;

	void open(const char* filename);
};


void Classfile::open(const char* filename)
{
	FILE* fp = fopen(filename, "rb");
	assert(fp != nullptr);

	auto read8  = [&]() -> uint8_t { return fgetc(fp); };
	auto read16 = [&]() -> uint16_t { return (read8() << 8) | read8(); };
	auto read32 = [&]() -> uint32_t { return (read16() << 16) | read16(); };

	uint32_t magic = read32();
	printf("magic: 0x%04x\n", magic);

	uint16_t minor = read16();
	uint16_t major = read16();
	printf("version: %d.%d\n", major, minor);

	uint16_t constantCount = read16() - 1;
	printf("constant count: %u\n", constantCount);

	for (int i = 0; i < constantCount; ++i) {
		ConstantTag tag = (ConstantTag) read8();
		switch (tag) {
			case ConstantTag::Class:
				read16(); // name_index
				break;
			case ConstantTag::Fieldref:
				read16(); // class index
				read16(); // name and type index
				break;
			case ConstantTag::Methodref:
				read16(); // class index
				read16(); // name and type index
				break;
			case ConstantTag::InterfaceMethodref:
				read16(); // class index
				read16(); // name and type index
				break;
			case ConstantTag::String:
				read16(); // string index
				break;
			case ConstantTag::Integer:
				read32();
				break;
			case ConstantTag::Float:
				read32();
				break;
			case ConstantTag::Long:
				read32(); // high
				read32(); // low
				break;
			case ConstantTag::Double:
				read32();
				read32();
				break;
			case ConstantTag::NameAndType:
				read16(); // name index
				read16(); // descriptor index
				break;
			case ConstantTag::Utf8: {
				uint16_t length = read16();
				uint8_t* buf = new uint8_t[length + 1];
				fread(buf, length, 1, fp);
				buf[length] = '\0';
				printf("\tUtf8: %s\n", buf);
				delete[] buf;
				break;
			}
			case ConstantTag::MethodHandle:
				read8(); // reference kind
				read16(); // reference index
				break;
			case ConstantTag::MethodType:
				read16(); // descriptor index
				break;
			case ConstantTag::InvokeDynamic: {
				uint16_t bootstrapMethodAttrIndex = read16();
				uint16_t nameAndTypeIndex = read16();
				break;
			}
			default: {
				break;
			}
		}
	}

	uint16_t accessFlags = read16();
	printf("access flags: 0x%0x\n", accessFlags);

	uint16_t thisClass = read16();
	uint16_t superClass = read16();
	uint16_t interfaceCount = read16();
	uint16_t* interfaces = new uint16_t[interfaceCount];
	fread(interfaces, interfaceCount, sizeof(uint16_t), fp);

	printf("this class: %u\n", thisClass);
	printf("super class: %u\n", superClass);
	printf("interface count: %u\n", interfaceCount);

	uint16_t fieldCount = read16();
	printf("field count: %u\n", fieldCount);

	for (int i = 0; i < fieldCount; ++i) {
		uint16_t accessFlags = read16();
		uint16_t nameIndex = read16();
		uint16_t descriptorIndex = read16();
		uint16_t attributesCount = read16();

		// attribute_info
		for (int u = 0; u < attributesCount; ++u) {
			uint16_t nameIndex = read16();
			uint32_t attributeLength = read32();
			uint8_t* info = new uint8_t[attributeLength];
			fread(info, attributeLength, sizeof(uint8_t), fp);
			delete[] info;
		}
	}

	uint16_t methodCount = read16();
	printf("method count: %u\n", methodCount);

	for (int i = 0; i < methodCount; ++i) {
		uint16_t accessFlags = read16();
		uint16_t nameIndex = read16();
		uint16_t descriptorIndex = read16();
		uint16_t attributesCount = read16();

		// attribute_info
		for (int u = 0; u < attributesCount; ++u) {
			uint16_t nameIndex = read16();
			uint32_t attributeLength = read32();
			uint8_t* info = new uint8_t[attributeLength];
			fread(info, attributeLength, sizeof(uint8_t), fp);
			delete[] info;
		}
	}

	fclose(fp);
}

int main(int argc, const char* argv[])
{
	Classfile c;
	c.open(argc == 2 ? argv[1] : "Test.class");
	return 0;
}
