#pragma once

#include "ConstantPool.h"
#include "Classfile.h"
#include <stdint.h>
#include <string>
#include <vector>

class Class;

class Field {
private:
	Class* thisClass_;
	ConstantUtf8* name_;
	ConstantUtf8* descriptor_;
	FieldFlags flags_;
	std::vector<Attribute*> attributes_;

public:
	Field(Class* thisClass, ConstantUtf8* name, ConstantUtf8* descriptor, FieldFlags flags) :
		thisClass_(thisClass),
		name_(name),
		descriptor_(descriptor),
		flags_(flags),
		attributes_()
	{}

	Class* thisClass() const { return thisClass_; }
	const char* name() const { return name_->c_str(); }
	const char* descriptor() const { return descriptor_->c_str(); }
	FieldFlags flags() const { return flags_; }
	const std::vector<Attribute*>& attributes() const { return attributes_; }
	std::vector<Attribute*>& attributes() { return attributes_; }

	void dump() const;
};

class Method {
public:
	friend class Class;
	friend class VMClassLoader;

	struct ExceptionHandler {
		uint16_t start;
		uint16_t end;
		uint16_t handler;
		uint16_t type;

		ExceptionHandler(uint16_t _start, uint16_t _end, uint16_t _handler, uint16_t _type) :
			start(_start), end(_end), handler(_handler), type(_type) {}
	};

	struct StackMapFrame {
		uint8_t type;

#if 0
		union {
			// type == SAME /* 0-63 */

			// type == SAME_LOCALS_1_STACK_ITEM /* 64-127 */
			struct {
				verification_type_info stack[1];
			} same_locals_1_stack_item;

			// type == SAME_LOCALS_1_STACK_ITEM_EXTENDED /* 247 */
			struct {
				u2 offset_delta;
				verification_type_info stack[1];
			} same_locals_1_stack_item_frame_extended;

			// type == CHOP /* 248-250 */
			struct {
				uint16_t offset_delta;
			} chop_frame;

			// type == SAME_FRAME_EXTENDED /* 251 */
			struct {
				uint16_t offset_delta;
			} same_frame_extended;

			// type == APPEND /* 252-254 */
			struct {
				uint16_t offset_delta;
				verification_type_info locals[frame_type - 251]; // XXX wtf?
			} append_frame;
		} u;
#endif
	};

	struct LineNumber {
		uint16_t start; // offset into code
		uint16_t line; // source code line number
	};

private:
	std::string name_;
	std::string signature_;
	MethodFlags flags_;
	uint16_t maxStack_;
	uint16_t maxLocals_;
	bool isDeprecated_;
	std::vector<uint8_t> code_;
	std::vector<ExceptionHandler> exceptionTable_;
	std::vector<StackMapFrame> stackMapTable_;
	std::vector<LineNumber> lineNumberTable_;

public:
	Method(ConstantUtf8* name, ConstantUtf8* signature, MethodFlags flags) :
		name_(name->c_str()),
		signature_(signature->c_str()),
		flags_(flags),
		maxStack_(0),
		maxLocals_(0),
		isDeprecated_(false),
		code_(),
		exceptionTable_()
	{
	}

	const std::string& name() const { return name_; }
	const std::string& signature() const { return signature_; }
	MethodFlags flags() const { return flags_; }

	uint16_t maxStack() const { return maxStack_; }
	uint16_t maxLocals() const { return maxLocals_; }
	bool isDeprecated() const { return isDeprecated_; }
	const std::vector<uint8_t>& code() const { return code_; }
	const std::vector<ExceptionHandler>& exceptionTable() const { return exceptionTable_; }
	const std::vector<StackMapFrame>& stackMapTable() const { return stackMapTable_; }
	const std::vector<LineNumber>& lineNumberTable() const { return lineNumberTable_; }

	std::string to_s() const;
	void dump() const;
};

class Class {
private:
	std::string sourceFile_;
	int major_;
	int minor_;

	ClassFlags flags_;
	std::string thisClassName_;
	ConstantClass* thisClass_;

	std::string superClassName_;
	Class* superClass_;

	std::vector<uint16_t> interfaceIds_;
	std::vector<Class*> interfaces_;

	std::vector<Field*> fields_;
	std::vector<Method*> methods_;

private:
	Class();
	~Class();

	friend class VMClassLoader;

public:
	ConstantPool constantPool;

public:
	const std::string& name() const { return thisClassName_; }
	bool isLoaded() const { return major_ != 0; }
	const std::string& sourceFileName() const { return sourceFile_; }
	int versionMajor() const { return major_; }
	int versionMinor() const { return minor_; }

	Class* superClass() const { return superClass_; }
	ClassFlags flags() const { return flags_; }

	Method* findMethod(const std::string& name);

	void resolve();

	void dump();
};

