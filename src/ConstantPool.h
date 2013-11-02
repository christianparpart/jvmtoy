#pragma once

#include <string>
#include <vector>
#include <stdint.h>

enum class ConstantTag {
	Class = 7,
	Fieldref = 9,
	Methodref = 10,
	InterfaceMethodref = 11,
	String = 8,
	Integer = 3,
	Float = 4,
	Long = 5,
	Double = 6,
	NameAndType = 12,
	Utf8 = 1,
	MethodHandle = 15,
	MethodType = 16,
	InvokeDynamic = 18,
};

inline std::string tos(ConstantTag value) {
	switch (value) {
		case ConstantTag::Class: return "Class";
		case ConstantTag::Fieldref: return "Fieldref";
		case ConstantTag::Methodref: return "Methodref";
		case ConstantTag::InterfaceMethodref: return "InterfaceMethodref";
		case ConstantTag::String: return "String";
		case ConstantTag::Integer: return "Integer";
		case ConstantTag::Float: return "FLoat";
		case ConstantTag::Long: return "Long";
		case ConstantTag::Double: return "Double";
		case ConstantTag::NameAndType: return "NameAndType";
		case ConstantTag::Utf8: return "Utf8";
		case ConstantTag::MethodHandle: return "MethodHandle";
		case ConstantTag::MethodType: return "MethodType";
		case ConstantTag::InvokeDynamic: return "InvokeDynamic";
		default: return "UNKNOWN";
	}
}

struct Constant {
	ConstantTag tag;

	Constant(ConstantTag t) : tag(t) {}

	//! Returns a debug-friendly string representation of given constant.
	virtual std::string to_s() const = 0;
};

struct ConstantInteger : public Constant {
	int16_t value;

	ConstantInteger(int16_t val) : Constant(ConstantTag::Integer), value(val) {}

	virtual std::string to_s() const {
		char buf[64];
		snprintf(buf, sizeof(buf), "%s: %i", tos(tag).c_str(), value);
		return buf;
	}
};

struct ConstantLong : public Constant {
	int64_t value;

	ConstantLong(int64_t val) : Constant(ConstantTag::Long), value(val) {}

	virtual std::string to_s() const {
		char buf[64];
		snprintf(buf, sizeof(buf), "%s: 0x%08llX (%li)", tos(tag).c_str(), (value & 0xFFFFFFFFllu), value);
		return buf;
	}
};

struct ConstantUtf8 : public Constant {
	uint16_t length;
	uint8_t* data;

	ConstantUtf8(uint16_t len, uint8_t* d) : Constant(ConstantTag::Utf8), length(len), data(d) {}
	~ConstantUtf8() { delete[] data; }

	const char* c_str() const { return (const char*) data; }

	virtual std::string to_s() const {
		char buf[256];
		snprintf(buf, sizeof(buf), "%s: %s", tos(tag).c_str(), data);
		return buf;
	}
};

struct ConstantClass : public Constant {
	uint16_t id;
	ConstantUtf8* name;

	ConstantClass(uint16_t nameId, ConstantUtf8* value) :
		Constant(ConstantTag::Class),
		id(nameId),
		name(value)
	{}

	virtual std::string to_s() const {
		char buf[256];
		snprintf(buf, sizeof(buf), "%s: #%d: %s", tos(tag).c_str(), id, name->c_str());
		return buf;
	}
};

class ConstantPool {
	typedef std::vector<Constant*> vector_type;

	vector_type pool;

public:
	ConstantPool() { }
	~ConstantPool() { }

	void resize(size_t size) { pool.resize(size); }
	size_t size() const { return pool.size(); }
	vector_type::iterator begin() { return pool.begin(); }
	vector_type::iterator end() { return pool.end(); }
	const Constant* operator[](size_t id) const { return pool[id]; }
	Constant*& operator[](size_t id) { return pool[id]; }

	ConstantUtf8* getUtf8(size_t id) {
		if (id < 1 || id >= pool.size() || pool[id]->tag != ConstantTag::Utf8)
			return nullptr;

		return static_cast<ConstantUtf8*>(pool[id]);
	}
};

