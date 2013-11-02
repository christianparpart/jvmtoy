#include "ConstantPool.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <string>
#include <initializer_list>

enum class AccessFlag {
	Public      = 0x0001,
	Final       = 0x0010,
	Super       = 0x0020,
	Interactive = 0x0200,
	Abstract    = 0x0400,
	Synthetic   = 0x1000,
	Annotation  = 0x2000,
	Enum        = 0x4000,
};

uint32_t operator|(AccessFlag a, AccessFlag b) {
	return ((uint32_t)a) | ((uint32_t)b);
}

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

	uint16_t constantCount = read16();
	printf("constant count: %u\n", constantCount);

	struct class_const { uint16_t selfIndex; uint16_t nameIndex; };
	struct member_const { uint16_t selfIndex; ConstantTag tag; uint16_t classIndex; uint16_t nameAndTypeIndex; };
	struct nameandtype_const { uint16_t selfIndex; uint16_t nameIndex; uint16_t signatureIndex; };
	struct string_const { uint16_t selfIndex; uint16_t stringIndex; };

	std::vector<class_const> class_consts;
	std::vector<member_const> member_consts;
	std::vector<nameandtype_const> nameandtype_consts;
	std::vector<string_const> string_consts;

	constantPool.resize(constantCount + 1);
	for (auto& slot: constantPool)
		slot = nullptr;

	for (uint16_t i = 1; i < constantCount; ++i) {
		ConstantTag tag = (ConstantTag) read8();
		printf("[%d] tag: %s\n", i, tos(tag).c_str());
		switch (tag) {
			case ConstantTag::Class: {
				uint16_t nameIndex = read16();
				class_consts.push_back({i, nameIndex});
				break;
			}
			case ConstantTag::Fieldref:
			case ConstantTag::Methodref:
			case ConstantTag::InterfaceMethodref: {
				uint16_t classIndex = read16();
				uint16_t nameAndTypeIndex = read16();
				member_consts.push_back({i, tag, classIndex, nameAndTypeIndex});
				break;
			}
			case ConstantTag::String: {
				uint16_t stringIndex = read16();
				string_consts.push_back({i, stringIndex});
				break;
			}
			case ConstantTag::Integer: {
				uint32_t value = read32();
				printf("\tInteger(%d)\n", value);
				constantPool[i] = new ConstantInteger(value);
				break;
			}
			case ConstantTag::Float: {
				read32();
				break;
			}
			case ConstantTag::Long: {
				uint64_t value = read32();
				value <<= 32;
				value |= read32();
				printf("\tLong(%li)\n", value);
				constantPool[i] = new ConstantLong(value);
				++i;
				break;
			}
			case ConstantTag::Double: {
				read32();
				read32();
				++i;
				break;
			}
			case ConstantTag::NameAndType: {
				uint16_t nameIndex = read16();
				uint16_t signatureIndex = read16();
				nameandtype_consts.push_back({i, nameIndex, signatureIndex});
				break;
			}
			case ConstantTag::Utf8: {
				uint16_t length = read16();
				uint8_t* buf = new uint8_t[length + 1];
				fread(buf, length, 1, fp);
				buf[length] = '\0';
				constantPool[i] = new ConstantUtf8(length, buf);
				printf("\t%s\n", ((ConstantUtf8*)constantPool[i])->c_str());
				break;
			}
			case ConstantTag::MethodHandle: {
				uint8_t kind = read8(); // reference kind
				uint16_t index = read16(); // reference index
				printf(" (kind: %d, index: %d)\n", kind, index);
				break;
			}
			case ConstantTag::MethodType: {
				read16(); // descriptor index
				break;
			}
			case ConstantTag::InvokeDynamic: {
				uint16_t bootstrapMethodAttrIndex = read16();
				uint16_t nameAndTypeIndex = read16();
				printf("\t%d %d\n", bootstrapMethodAttrIndex, nameAndTypeIndex);
				break;
			}
			default: {
				abort();
				break;
			}
		}
	}

	for (const auto& rec: class_consts) {
		ConstantUtf8* name = constantPool.getUtf8(rec.nameIndex);
		printf("Class #%u: %s\n", rec.selfIndex, name->c_str());
		constantPool[rec.selfIndex] = new ConstantClass(rec.nameIndex, name);
	}

	printf("-----------------------------------------\n");
	printf("CONSTANT_POOL:\n");
	for (int k = 0; k < constantPool.size(); ++k)
		printf("\t[%d] %s\n", k, constantPool[k] ? constantPool[k]->to_s().c_str() : "null");
	printf("-----------------------------------------\n");

	uint16_t accessFlags = read16();
	printf("access flags: 0x%0x\n", accessFlags);

	uint16_t thisClass = read16();
	uint16_t superClass = read16();
	uint16_t interfaceCount = read16();
	uint16_t* interfaces = new uint16_t[interfaceCount];
	fread(interfaces, interfaceCount, sizeof(uint16_t), fp);

	printf("this class: %s\n", constantPool[thisClass]->to_s().c_str());
	printf("super class: %s\n", constantPool[superClass]->to_s().c_str());
	printf("interface count: %u\n", interfaceCount);

	uint16_t fieldCount = read16();
	printf("field count: %u\n", fieldCount);

	for (int i = 0; i < fieldCount; ++i) {
		uint16_t accessFlags = read16();
		uint16_t nameIndex = read16();
		uint16_t descriptorIndex = read16();
		uint16_t attributeCount = read16();
		printf("[%d] name: %d\n", i, nameIndex);

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			uint32_t length = read32();
			uint8_t* info = new uint8_t[length];
			fread(info, length, sizeof(uint8_t), fp);
			ConstantUtf8* name = constantPool.getUtf8(nameIndex);
			printf("    attribute: %u (%s) %d\n", nameIndex, name->c_str(), length);
			delete[] info;
		}
	}

	uint16_t methodCount = read16();
	printf("method count: %u\n", methodCount);

	for (int i = 0; i < methodCount; ++i) {
		uint16_t accessFlags = read16();
		uint16_t nameIndex = read16();
		uint16_t descriptorIndex = read16();
		uint16_t attributeCount = read16();
		ConstantUtf8* name = constantPool.getUtf8(nameIndex);
		printf("[%d] name: %d (%s)\n", i, nameIndex, name->c_str());

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			ConstantUtf8* name = constantPool.getUtf8(nameIndex);
			uint32_t length = read32();
			uint8_t* info = new uint8_t[length];
			fread(info, length, sizeof(uint8_t), fp);
			printf("    attribute: %u (%s) %d\n", nameIndex, name->c_str(), length);
			delete[] info;
		}
	}

	uint16_t attributeCount = read16();
	printf("attribute count: %u\n", attributeCount);
	for (int i = 0; i < attributeCount; ++i) {
		uint16_t nameIndex = read16();
		uint32_t length = read32();
		uint8_t *info = new uint8_t[length];
		fread(info, length, sizeof(uint8_t), fp);
		printf("    %u %d\n", nameIndex, length);
	}

	fclose(fp);
}

int main(int argc, const char* argv[])
{
	Classfile c;
	c.open(argc == 2 ? argv[1] : "tests/Test.class");
	return 0;
}
