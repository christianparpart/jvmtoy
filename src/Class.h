#pragma once

#include "ConstantPool.h"
#include <stdint.h>
#include <string>
#include <vector>

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

uint32_t operator|(AccessFlags a, AccessFlags b) {
	return ((uint32_t)a) | ((uint32_t)b);
}

bool operator&(AccessFlags a, AccessFlags b) {
	return ((uint32_t)a) & ((uint32_t)b);
}

std::string tos(AccessFlags flags);

class Class {
private:
	std::string filename_;

	Class* superClass_;
	std::vector<Class*> interfaces_;

private:
	Class(const std::string& filename);
	bool load();

public:
	ConstantPool constantPool;

public:
	~Class();

	Class* superClass() const { return superClass_; }
	AccessFlags accessFlags() const;

	static Class* load(const char* filename);
};

