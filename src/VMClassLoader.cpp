#include "VMClassLoader.h"
#include "ConstantPool.h"
#include "Class.h"
#include "JvmEnv.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

VMClassLoader::VMClassLoader() :
	classes_(),
	classpaths_()
{
	classpaths_.push_back(".");
}

VMClassLoader::~VMClassLoader()
{
}

void VMClassLoader::addClassPath(const std::string& path)
{
	classpaths_.push_back(path);
}

Class* VMClassLoader::findClass(const char* className)
{
	auto i = classes_.find(className);
	if (i != classes_.end()) {
		printf("findClass(%s) -> found\n", className);
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

		struct stat st;
		if (stat(path.c_str(), &st) < 0)
			continue;

		int fd = open(path.c_str(), O_RDONLY);
		if (fd < 0)
			continue;

		uint8_t* classfile = (uint8_t*) mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (!classfile) {
			close(fd);
			return nullptr;
		}

		Class* result = defineClass(className, classfile, st.st_size);

		munmap(classfile, st.st_size);
		close(fd);

		return result;
	}
	return nullptr;
}

Class* VMClassLoader::defineClass(const char* className, const uint8_t* classfile, size_t size)
{
	size_t readOffset = 0;

	auto read8  = [&]() -> uint8_t {
		if (readOffset < size)
			return classfile[readOffset++];
		else
			return EOF;
	};

	auto read16 = [&]() -> uint16_t {
		return (read8() << 8) | read8();
	};

	auto read32 = [&]() -> uint32_t {
		return (read16() << 16) | read16();
	};

	auto consume = [&](size_t n) {
		readOffset += n;
	};

	auto readn = [&](uint8_t* buf, size_t n) {
		for (size_t i = 0; i < n; ++i)
			buf[i] = read8();
	};

	// -------------------------------------------------------------------------

	uint32_t magic = read32();
	if (magic != 0xcafebabe) {
		// wrong classfile magic
		return nullptr;
	}

	Class* c = new Class();
	classes_[className] = c;

	c->minor_ = read16();
	c->major_ = read16();

	uint16_t constantCount = read16();

	struct class_const { uint16_t selfIndex; uint16_t nameIndex; };
	struct member_const { uint16_t selfIndex; ConstantTag tag; uint16_t classIndex; uint16_t nameAndTypeIndex; };
	struct nameandtype_const { uint16_t selfIndex; uint16_t nameIndex; uint16_t signatureIndex; };
	struct string_const { uint16_t selfIndex; uint16_t stringIndex; };

	std::vector<class_const> class_consts;
	std::vector<member_const> member_consts;
	std::vector<nameandtype_const> nameandtype_consts;
	std::vector<string_const> string_consts;

	c->constantPool.resize(constantCount);
	for (auto& slot: c->constantPool)
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
				c->constantPool[i] = new ConstantInteger(value);
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
				c->constantPool[i] = new ConstantLong(value);
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
				readn(buf, length);
				buf[length] = '\0';
				c->constantPool[i] = new ConstantUtf8(length, buf);
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
		ConstantUtf8* string = c->constantPool.get<ConstantUtf8>(rec.stringIndex);
		c->constantPool[rec.selfIndex] = new ConstantString(rec.stringIndex, string);
	}

	for (const auto& rec: nameandtype_consts) {
		ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(rec.nameIndex);
		ConstantUtf8* sig = c->constantPool.get<ConstantUtf8>(rec.signatureIndex);
		c->constantPool[rec.selfIndex] = new ConstantNameAndType(name, sig);
	}

	for (const auto& rec: class_consts) {
		ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(rec.nameIndex);
		c->constantPool[rec.selfIndex] = new ConstantClass(rec.nameIndex, name);
	}

	for (const auto& rec: member_consts) {
		ConstantClass* classRef = (ConstantClass*) c->constantPool[rec.classIndex];
		ConstantNameAndType* nametypeRef = (ConstantNameAndType*) c->constantPool[rec.nameAndTypeIndex];
		c->constantPool[rec.selfIndex] = new ConstantMember(rec.tag, classRef, nametypeRef);
	}

	c->flags_ = (ClassFlags) read16();

	uint16_t thisClassId = read16();
	uint16_t superClassId = read16();
	uint16_t interfaceCount = read16();
	c->interfaceIds_.resize(interfaceCount);
	c->interfaces_.resize(c->interfaceIds_.size());
	for (size_t i = 0; i < interfaceCount; ++i) {
		uint16_t id = read16();
		c->interfaceIds_[i] = id;
		c->interfaces_[i] = nullptr;
	}

	c->thisClass_ = c->constantPool.get<ConstantClass>(thisClassId);
	c->thisClassName_ = c->thisClass_->name->c_str();

	if (superClassId != 0) {
		c->superClassName_ = c->constantPool.get<ConstantClass>(superClassId)->name->c_str();
		c->superClass_ = nullptr;
	}

	// class fields
	uint16_t fieldCount = read16();
	c->fields_.resize(fieldCount);
	for (int i = 0; i < fieldCount; ++i) {
		FieldFlags flags = (FieldFlags) read16();
		uint16_t nameIndex = read16();
		uint16_t descriptorIndex = read16();
		uint16_t attributeCount = read16();

		ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(nameIndex);
		ConstantUtf8* desc = c->constantPool.get<ConstantUtf8>(descriptorIndex);

		Field* field = new Field(c, name, desc, flags);
		c->fields_[i] = field;

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			uint32_t length = read32();

			consume(length); // TODO evaluate instead of consuming

			ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(nameIndex);
			printf("Class field attribute: #%u %s length: %d\n", nameIndex, name->c_str(), length);
		}
	}

	uint16_t methodCount = read16();
	for (int i = 0; i < methodCount; ++i) {
		MethodFlags flags = (MethodFlags) read16();
		ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(read16());
		ConstantUtf8* desc = c->constantPool.get<ConstantUtf8>(read16());
		uint16_t attributeCount = read16();

		Method* method = new Method(name, desc, flags);
		c->methods_.push_back(method);

		// attribute_info
		for (int u = 0; u < attributeCount; ++u) {
			uint16_t nameIndex = read16();
			ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(nameIndex);
			uint32_t length = read32();

			if (equals(name, "Deprecated")) {
				method->isDeprecated_ = true;
			} else if (equals(name, "Signature")) {
				uint16_t signatureId = read16();
				ConstantUtf8* signatureStr = c->constantPool.get<ConstantUtf8>(signatureId);
				printf("Method %s has signature attribute %s\n",
					method->to_s().c_str(),
					signatureStr->c_str()
				);
			} else if (equals(name, "Code")) {
				method->maxStack_ = read16();
				method->maxLocals_ = read16();

				uint32_t codeLength = read32();
				method->code_.resize(codeLength);
				readn(&method->code_[0], codeLength);

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
					ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(nameId);

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

		ConstantUtf8* name = c->constantPool.get<ConstantUtf8>(nameId);

		if (equals(name, "SourceFile")) {
			uint16_t value = read16();
			ConstantUtf8* sourceFile = c->constantPool.get<ConstantUtf8>(value);
			c->sourceFile_ = sourceFile->c_str();
		} else {
			printf("WARNING: Unhandled classfile attribute #%d: name #%d (length: %d)\n", i, nameId, length);
			consume(length);
		}
	}

	return c;
}

void VMClassLoader::resolveClass(Class* c)
{
	// link class c, resolving any unresolved symbols

	for (size_t i = 0; i < c->interfaceIds_.size(); ++i) {
		if (c->interfaces_[i])
			continue;

		uint16_t id = c->interfaceIds_[i];
		ConstantClass* interface = c->constantPool.get<ConstantClass>(id);
		printf("interface #%zu: #%d %s\n", i, id, interface ? interface->name->c_str() : "???");
		c->interfaces_[i] = findClass(interface->name->c_str());
	}

	if (!c->superClass_) {
		c->superClass_ = findClass(c->superClassName_.c_str());
	}

	// TODO
	// field/method signature types ...
}
