#pragma once

#include "ConstantPool.h"
#include "Classfile.h"
#include <stdint.h>
#include <string>
#include <vector>

class Field {
private:
	ConstantUtf8* name_;
	ConstantUtf8* descriptor_;
	std::vector<Attribute*> attributes_;

public:
	Field(ConstantUtf8* name, ConstantUtf8* descriptor) :
		name_(name),
		descriptor_(descriptor),
		attributes_()
	{}

	const char* name() const { return name_->c_str(); }
	const char* descriptor() const { return descriptor_->c_str(); }
	const std::vector<Attribute*>& attributes() const { return attributes_; }
	std::vector<Attribute*>& attributes() { return attributes_; }
};

class Method {
};

class Class {
private:
	std::string sourceFile_;
	int major_;
	int minor_;

	AccessFlags accessFlags_;
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
	bool _load(const char* filename);

public:
	ConstantPool constantPool;

public:
	~Class();

	bool isLoaded() const { return major_ != 0; }
	const std::string& sourceFileName() const { return sourceFile_; }
	int versionMajor() const { return major_; }
	int versionMinor() const { return minor_; }

	Class* superClass() const { return superClass_; }
	AccessFlags accessFlags() const;

	static Class* load(const char* filename);

	void dump();
};

