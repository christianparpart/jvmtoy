#pragma once

#include <stdint.h>

#define JVM_PACKED __attribute__((packed))

// class file format structs

struct JVM_PACKED Attribute {
	uint16_t nameId;
	uint32_t length;
};

struct JVM_PACKED ConstantValueAttribute : public Attribute {
	uint16_t valueId;
};

struct JVM_PACKED CodeAttribute : public Attribute {
	struct JVM_PACKED ExceptionTable : public Attribute {
		uint16_t start_pc;
		uint16_t end_pc;
		uint16_t handler_pc;
		uint16_t catchType;
	};

	uint16_t maxStack;
	uint16_t maxLocals;
	uint32_t codeLength;
	uint8_t code[];

//	uint16_t exceptionTableLength;
//	...
};

struct JVM_PACKED SourceFileAttribute : public Attribute {
	uint16_t sourceFileId;
};

struct JVM_PACKED SignatureAttribute : public Attribute {
	uint16_t signatureId;
};

// ----------------------------------------------------------------------

enum class ClassFlags {
	Public      = 0x0001,
	Final       = 0x0010,
	Super       = 0x0020,
	Interactive = 0x0200,
	Abstract    = 0x0400,
	Synthetic   = 0x1000,
	Annotation  = 0x2000,
	Enum        = 0x4000,
};

enum class MethodFlags {
	Public       = 0x0001,
	Private      = 0x0002,
	Protected    = 0x0004,
	Static       = 0x0008,
	Final        = 0x0010,
	Synchronized = 0x0020,
	Bridge       = 0x0040,
	VarArgs      = 0x0080,
	Native       = 0x0100,
	Abstract     = 0x0400,
	Strict       = 0x0800,
	Synthetic    = 0x1000
};

enum class FieldFlags {
	Public      = 0x0001,
	Private     = 0x0002,
	Protected   = 0x0004,
	Static      = 0x0008,
	Final       = 0x0010,
	Volatile    = 0x0040,
	Transient   = 0x0080,
	Synthetic   = 0x1000,
	Enum        = 0x4000,
};

inline uint32_t operator|(ClassFlags a, ClassFlags b) { return ((uint32_t)a) | ((uint32_t)b); }
inline bool operator&(ClassFlags a, ClassFlags b) { return ((uint32_t)a) & ((uint32_t)b); }
std::string tos(ClassFlags flags);

inline uint32_t operator|(MethodFlags a, MethodFlags b) { return ((uint32_t)a) | ((uint32_t)b); }
inline bool operator&(MethodFlags a, MethodFlags b) { return ((uint32_t)a) & ((uint32_t)b); }
std::string tos(MethodFlags flags);

inline uint32_t operator|(FieldFlags a, FieldFlags b) { return ((uint32_t)a) | ((uint32_t)b); }
inline bool operator&(FieldFlags a, FieldFlags b) { return ((uint32_t)a) & ((uint32_t)b); }
std::string tos(FieldFlags flags);

