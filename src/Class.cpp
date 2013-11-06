#include "Class.h"
#include "ConstantPool.h"
#include "JvmEnv.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <string>
#include <initializer_list>

// {{{ tos() impls
std::string tos(ClassFlags flags)
{
	static const struct {
		ClassFlags value;
		const char* name;
	} map[] = {
		{ ClassFlags::Public, "public" },
		{ ClassFlags::Final, "final" },
		{ ClassFlags::Super, "super" },
		{ ClassFlags::Interactive, "interactive" },
		{ ClassFlags::Abstract, "abstract" },
		{ ClassFlags::Synthetic, "synthetic" },
		{ ClassFlags::Annotation, "annotation" },
		{ ClassFlags::Enum, "enum" },
	};

	std::vector<std::string> set;
	for (const auto& flag: map)
		if (flag.value & flags)
			set.push_back(flag.name);

	std::string s;
	for (size_t i = 0, e = set.size(); i != e; ++i) {
		if (i) s += " ";
		s += set[i];
	}
	return s;
}

std::string tos(MethodFlags flags)
{
	static const struct {
		MethodFlags value;
		const char* name;
	} map[] = {
		{ MethodFlags::Public, "public" },
		{ MethodFlags::Private, "private" },
		{ MethodFlags::Protected, "protected" },
		{ MethodFlags::Static, "static" },
		{ MethodFlags::Final, "final" },
		{ MethodFlags::Synchronized, "synchronized" },
		{ MethodFlags::Bridge, "bridge" },
		{ MethodFlags::VarArgs, "varargs" },
		{ MethodFlags::Native, "native" },
		{ MethodFlags::Abstract, "abstract" },
		{ MethodFlags::Strict, "strict" },
		{ MethodFlags::Synthetic, "synthetic" },
	};

	std::vector<std::string> set;
	for (const auto& flag: map)
		if (flag.value & flags)
			set.push_back(flag.name);

	std::string s;
	for (size_t i = 0, e = set.size(); i != e; ++i) {
		if (i) s += " ";
		s += set[i];
	}
	return s;
}

std::string tos(FieldFlags flags)
{
	static const struct {
		FieldFlags value;
		const char* name;
	} map[] = {
		{ FieldFlags::Public, "public" },
		{ FieldFlags::Private, "private" },
		{ FieldFlags::Protected, "protected" },
		{ FieldFlags::Static, "static" },
		{ FieldFlags::Final, "final" },
		{ FieldFlags::Volatile, "volatile" },
		{ FieldFlags::Transient, "transient" },
		{ FieldFlags::Synthetic, "synthetic" },
		{ FieldFlags::Enum, "enum" },
	};

	std::vector<std::string> set;
	for (const auto& flag: map)
		if (flag.value & flags)
			set.push_back(flag.name);

	std::string s;
	for (size_t i = 0, e = set.size(); i != e; ++i) {
		if (i) s += " ";
		s += set[i];
	}
	return s;
}
// }}}

Class::Class(JvmEnv* env) :
	env_(env),
	sourceFile_(),
	major_(0),
	minor_(0),
	flags_()
{
}

Class::~Class()
{
}

bool Class::load(const std::string& filename)
{
	FILE* fp = fopen(filename.c_str(), "rb");
	assert(fp != nullptr);

	auto read8  = [&]() -> uint8_t { return fgetc(fp); };
	auto read16 = [&]() -> uint16_t { return (read8() << 8) | read8(); };
	auto read32 = [&]() -> uint32_t { return (read16() << 16) | read16(); };
	auto consume = [&](size_t n) { for (size_t i = 0; i < n; ++i) read8(); };

	uint32_t magic = read32();

	if (magic != 0xcafebabe) {
		// wrong classfile magic
		return false;
	}

	minor_ = read16();
	major_ = read16();

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
				constantPool[i] = new ConstantInteger(value);
				break;
			}
			case ConstantTag::Float: { // TODO
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
			case ConstantTag::Double: { // TODO
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
			case ConstantTag::MethodHandle: { // TODO
				/*uint8_t kind =*/ read8(); // reference kind
				/*uint16_t index =*/ read16(); // reference index
				break;
			}
			case ConstantTag::MethodType: { // TODO
				read16(); // descriptor index
				break;
			}
			case ConstantTag::InvokeDynamic: { // TODO
				/*uint16_t bootstrapMethodAttrIndex =*/ read16();
				/*uint16_t nameAndTypeIndex =*/ read16();
				break;
			}
			default: {
				assert(!"FIXME");
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

	flags_ = (ClassFlags) read16();

	uint16_t thisClassId = read16();
	uint16_t superClassId = read16();
	uint16_t interfaceCount = read16();
	interfaceIds_.resize(interfaceCount);
	interfaces_.resize(interfaceIds_.size());
	for (size_t i = 0; i < interfaceCount; ++i) {
		uint16_t id = read16();
		interfaceIds_[i] = id;
		ConstantClass* interface = constantPool.get<ConstantClass>(id);
		printf("interface #%zu: #%d %s\n", i, id, interface ? interface->name->c_str() : "???");
		interfaces_[i] = env_->getClass(interface->name->c_str());
	}

	thisClass_ = constantPool.get<ConstantClass>(thisClassId);
	thisClassName_ = thisClass_->name->c_str();

	if (superClassId != 0) {
		superClassName_ = constantPool.get<ConstantClass>(superClassId)->name->c_str();
		superClass_ = env_->getClass(superClassName_.c_str());
	}

	// class fields
	uint16_t fieldCount = read16();
	fields_.resize(fieldCount);
	for (int i = 0; i < fieldCount; ++i) {
		FieldFlags flags = (FieldFlags) read16();
		uint16_t nameIndex = read16();
		uint16_t descriptorIndex = read16();
		uint16_t attributeCount = read16();

		ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameIndex);
		ConstantUtf8* desc = constantPool.get<ConstantUtf8>(descriptorIndex);

		Field* field = new Field(this, name, desc, flags);
		fields_[i] = field;

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			uint32_t length = read32();

			consume(length); // TODO evaluate instead of consuming

			ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameIndex);
			printf("Class field attribute: #%u %s length: %d\n", nameIndex, name->c_str(), length);
		}
	}

	uint16_t methodCount = read16();
	for (int i = 0; i < methodCount; ++i) {
		MethodFlags flags = (MethodFlags) read16();
		ConstantUtf8* name = constantPool.get<ConstantUtf8>(read16());
		ConstantUtf8* desc = constantPool.get<ConstantUtf8>(read16());
		uint16_t attributeCount = read16();

		Method* method = new Method(name, desc, flags);
		methods_.push_back(method);

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameIndex);
			uint32_t length = read32();

			if (equals(name, "Deprecated")) {
				method->isDeprecated_ = true;
			} else if (equals(name, "Signature")) {
				uint16_t signatureId = read16();
				ConstantUtf8* signatureStr = constantPool.get<ConstantUtf8>(signatureId);
				printf("Method %s has signature attribute %s\n",
					method->to_s().c_str(),
					signatureStr->c_str()
				);
			} else if (equals(name, "Code")) {
				method->maxStack_ = read16();
				method->maxLocals_ = read16();

				uint32_t codeLength = read32();
				method->code_.resize(codeLength);
				fread(&method->code_[0], codeLength, 1, fp);

				uint16_t exceptionTableLength = read16();
				for (uint16_t i = 0; i < exceptionTableLength; ++i) {
					uint16_t start = read16();
					uint16_t end = read16();
					uint16_t handler = read16();
					uint16_t type = read16();
					method->exceptionTable_.push_back({start, end, handler, type});
				}
				uint16_t attributeCount = read16();
				for (int i = 0; i < attributeCount; ++i) {
					uint16_t nameId = read16();
					uint32_t length = read32();
					ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameId);

					if (equals(name, "LineNumberTable")) {
						uint16_t count = read16();
						method->lineNumberTable_.resize(count);
						for (uint16_t i = 0; i < count; ++i) {
							uint16_t start = read16();
							uint16_t line = read16();
							method->lineNumberTable_[i] = {start, line};
						}
					} else if (equals(name, "LocalVariableTable")) {
						// TODO implement when we add debugging support
						consume(length);
					} else if (equals(name, "LocalVariableTypeTable")) {
						// TODO implement when we add debugging support
						consume(length);
					} else if (equals(name, "StackMapTable")) {
						// TODO needed for operand-stack type-checking (optional feature since classfile version 51.0)
						consume(length);
					} else {
						printf("WARNING: Unhandled method-code attribute %s for method %s\n", name->c_str(), method->to_s().c_str());
						// consume unhandled attribute payload
						consume(length);
					}
				}
			} else {
				printf("WARNING: Unhandled method attribute %s for method %s\n", name->c_str(), method->to_s().c_str());
				// consume unhandled attribute payload
				consume(length);
			}
		}
	}

	uint16_t attributeCount = read16();
	for (int i = 0; i < attributeCount; ++i) {
		uint16_t nameId = read16();
		uint32_t length = read32();

		ConstantUtf8* name = constantPool.get<ConstantUtf8>(nameId);

		if (equals(name, "SourceFile")) {
			uint16_t value = read16();
			ConstantUtf8* sourceFile = constantPool.get<ConstantUtf8>(value);
			sourceFile_ = sourceFile->c_str();
		} else {
			printf("WARNING: Unhandled classfile attribute #%d: name #%d (length: %d)\n", i, nameId, length);
			consume(length);
		}
	}

	fclose(fp);

	return true;
}

Method* Class::findMethod(const std::string& name)
{
	for (Method* method: methods_)
		if (method->name() == name)
			return method;

	return nullptr;
}

void Class::resolve()
{
}

void Class::dump()
{
	printf("-----------------------------------------------\n");
	printf("Version: %d.%d\n", major_, minor_);
	printf("This class: %s\n", thisClassName_.c_str());
	printf("Super class: %s\n", superClassName_.c_str());
	printf("Flags: %s\n", tos(flags_).c_str());
	printf("Interface count: %zu\n", interfaces_.size());

	printf("CONSTANT_POOL:\n");
	for (int k = 1; k < constantPool.size(); ++k) {
		printf("\t[%d] %s\n", k, constantPool[k] ? constantPool[k]->to_s().c_str() : "null");
	}

	printf("FIELDS: #%zu\n", fields_.size());
	for (int k = 0; k < fields_.size(); ++k) {
		Field* field = fields_[k];
		printf("\t[%d] ", k);
		field->dump();
	}

	printf("METHODS: #%zu\n", methods_.size());
	for (int k = 0; k < methods_.size(); ++k) {
		Method* method = methods_[k];
		printf("\t[%d] ", k);
		method->dump();
	}
}

void Field::dump() const
{
	printf("%s %s.%s: %s\n",
		tos(flags_).c_str(),
		thisClass_->name().c_str(),
		name_->c_str(),
		descriptor_->c_str()
	);
}

void Method::dump() const
{
	printf("%s %s: %s (code size: %zu)\n",
		tos(flags_).c_str(),
		name_.c_str(),
		signature_.c_str(),
		code_.size()
	);
}

std::string Method::to_s() const
{
	std::string s;

	s += name_;
	s += ": ";
	s += signature_;

	return s;
}
