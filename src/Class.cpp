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

Class::Class() :
	sourceFile_(),
	major_(0),
	minor_(0),
	flags_()
{
}

Class::~Class()
{
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
