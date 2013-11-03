#include "ConstantPool.h"
#include "Class.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <string>
#include <initializer_list>

std::string tos(AccessFlags flags) {
	std::string s;

	for (AccessFlags flag: {AccessFlags::Public,
							AccessFlags::Final,
							AccessFlags::Super,
							AccessFlags::Interactive,
							AccessFlags::Abstract,
							AccessFlags::Synthetic,
							AccessFlags::Annotation,
							AccessFlags::Enum})
	{
		if (!(flag & flags))
			continue;

		if (!s.empty())
			s += " ";

		switch (flag) {
			case AccessFlags::Public: s += "public"; break;
			case AccessFlags::Final: s += "final"; break;
			case AccessFlags::Super: s += "super"; break;
			case AccessFlags::Interactive: s += "interactive"; break;
			case AccessFlags::Abstract: s += "abstract"; break;
			case AccessFlags::Synthetic: s += "synthetic"; break;
			case AccessFlags::Annotation: s += "annotation"; break;
			case AccessFlags::Enum: s += "enum"; break;
			default:
				assert(!"FIXME");
				abort();
		}
	}

	return s;
}

Class::Class(const std::string& filename) :
	filename_(filename)
{
}

Class::~Class()
{
}

Class* Class::load(const char* filename)
{
	Class* c = new Class(filename);
	if (c->load())
		return c;

	delete c;
	return nullptr;
}

bool Class::load()
{
	FILE* fp = fopen(filename_.c_str(), "rb");
	assert(fp != nullptr);

	auto read8  = [&]() -> uint8_t { return fgetc(fp); };
	auto read16 = [&]() -> uint16_t { return (read8() << 8) | read8(); };
	auto read32 = [&]() -> uint32_t { return (read16() << 16) | read16(); };

	uint32_t magic = read32();

	if (magic != 0xCafeBabe)
		// wrong classfile magic
		return false;

	uint16_t minor = read16();
	uint16_t major = read16();

	uint16_t constantCount = read16();

	struct class_const { uint16_t selfIndex; uint16_t nameIndex; };
	struct member_const { uint16_t selfIndex; ConstantTag tag; uint16_t classIndex; uint16_t nameAndTypeIndex; };
	struct nameandtype_const { uint16_t selfIndex; uint16_t nameIndex; uint16_t signatureIndex; };
	struct string_const { uint16_t selfIndex; uint16_t stringIndex; };

	std::vector<class_const> class_consts;
	std::vector<member_const> member_consts;
	std::vector<nameandtype_const> nameandtype_consts;
	std::vector<string_const> string_consts;

	constantPool.resize(constantCount);
	for (auto& slot: constantPool)
		slot = nullptr;

	for (uint16_t i = 1; i < constantCount; ++i) {
		ConstantTag tag = (ConstantTag) read8();
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

	for (const auto& rec: string_consts) {
		ConstantUtf8* string = constantPool.get<ConstantUtf8>(rec.stringIndex);
		constantPool[rec.selfIndex] = new ConstantString(rec.stringIndex, string);
	}

	for (const auto& rec: nameandtype_consts) {
		ConstantUtf8* name = constantPool.get<ConstantUtf8>(rec.nameIndex);
		ConstantUtf8* sig = constantPool.get<ConstantUtf8>(rec.signatureIndex);
		constantPool[rec.selfIndex] = new ConstantNameAndType(name, sig);
	}

	for (const auto& rec: class_consts) {
		ConstantUtf8* name = constantPool.get<ConstantUtf8>(rec.nameIndex);
		constantPool[rec.selfIndex] = new ConstantClass(rec.nameIndex, name);
	}

	for (const auto& rec: member_consts) {
		ConstantClass* classRef = (ConstantClass*) constantPool[rec.classIndex];
		ConstantNameAndType* nametypeRef = (ConstantNameAndType*) constantPool[rec.nameAndTypeIndex];
		constantPool[rec.selfIndex] = new ConstantMember(rec.tag, classRef, nametypeRef);
	}

	AccessFlags accessFlags = (AccessFlags) read16();

	uint16_t thisClassId = read16();
	uint16_t superClassId = read16();
	uint16_t interfaceCount = read16();
	uint16_t* interfaces = new uint16_t[interfaceCount];
	fread(interfaces, interfaceCount, sizeof(uint16_t), fp);

	ConstantClass* thisClass = constantPool.get<ConstantClass>(thisClassId);
	ConstantClass* superClass = constantPool.get<ConstantClass>(superClassId);

	printf("magic: 0x%04x\n", magic);
	printf("version: %d.%d\n", major, minor);
	printf("constant count: %u\n", constantCount);
	printf("access flags: 0x%0x %s\n", accessFlags, tos(accessFlags).c_str());
	printf("this class: %s\n", thisClass->name->c_str());
	printf("super class: %s\n", superClass->name->c_str());
	printf("interface count: %u\n", interfaceCount);
	printf("-----------------------------------------\n");
	printf("CONSTANT_POOL:\n");
	for (int k = 0; k < constantPool.size(); ++k)
		printf("\t[%d] %s\n", k, constantPool[k] ? constantPool[k]->to_s().c_str() : "null");
	printf("-----------------------------------------\n");

	uint16_t fieldCount = read16();
	printf("field count: %u\n", fieldCount);

	for (int i = 0; i < fieldCount; ++i) {
		AccessFlags accessFlags = (AccessFlags) read16();
		uint16_t nameIndex = read16();
		uint16_t descriptorIndex = read16();
		uint16_t attributeCount = read16();

		ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameIndex);
		ConstantUtf8* desc = constantPool.get<ConstantUtf8>(descriptorIndex);

		printf("[%d] name: %s.%s: %s %s\n", i,
			thisClass->name->c_str(),
			name->c_str(),
			desc->c_str(),
			tos(accessFlags).c_str()
		);

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			uint32_t length = read32();
			uint8_t* info = new uint8_t[length];
			fread(info, length, sizeof(uint8_t), fp);
			ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameIndex);
			printf("    attribute: %u (%s) %d\n", nameIndex, name->c_str(), length);
			delete[] info;
		}
	}
	printf("-----------------------------------------\n");

	uint16_t methodCount = read16();
	printf("method count: %u\n", methodCount);

	for (int i = 0; i < methodCount; ++i) {
		AccessFlags accessFlags = (AccessFlags) read16();
		ConstantUtf8* name = constantPool.get<ConstantUtf8>(read16());
		ConstantUtf8* desc = constantPool.get<ConstantUtf8>(read16());
		uint16_t attributeCount = read16();

		printf("[%d] %s:%s %s\n", i,
			name->c_str(), desc->c_str(), tos(accessFlags).c_str());

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameIndex);
			uint32_t length = read32();
			uint8_t* info = new uint8_t[length];
			fread(info, length, sizeof(uint8_t), fp);
			printf("    attribute: %s (length: %d) ", name->c_str(), length);
			//for (int i = 0; i < length; ++i) printf("\\x%02x", info[i]);
			printf("\n");
			delete[] info;
		}
	}
	printf("-----------------------------------------\n");

	uint16_t attributeCount = read16();
	printf("attribute count: %u\n", attributeCount);
	for (int i = 0; i < attributeCount; ++i) {
		uint16_t nameId = read16();
		uint32_t length = read32();
		uint8_t *info = new uint8_t[length];

		ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameId);
		fread(info, length, sizeof(uint8_t), fp);
		printf("    %s (length: %u) ", name->c_str(), length);
		//for (int i = 0; i < length; ++i) printf("\\x%02x", info[i]);
		printf("\n");
	}

	fclose(fp);

	return true;
}

int main(int argc, const char* argv[])
{
	Class* c = Class::load(argc == 2 ? argv[1] : "tests/Test.class");
	delete c;

	return 0;
}
