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

enum class AccessFlags {
	Public      = 0x0001,
	Final       = 0x0010,
	Super       = 0x0020,
	Interactive = 0x0200,
	Abstract    = 0x0400,
	Synthetic   = 0x1000,
	Annotation  = 0x2000,
	Enum        = 0x4000,
};

inline uint32_t operator|(AccessFlags a, AccessFlags b) {
	return ((uint32_t)a) | ((uint32_t)b);
}

inline bool operator&(AccessFlags a, AccessFlags b) {
	return ((uint32_t)a) & ((uint32_t)b);
}

std::string tos(AccessFlags flags);

