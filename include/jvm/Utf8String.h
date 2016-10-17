#pragma once

#include <cstdint>
#include <string>

class Utf8String {
private:
	size_t size_;
	uint8_t* data_;

public:
	class iterator;
	class byte_iterator;

	struct ByteView;
	struct CharView;

	Utf8String();
	Utf8String(const uint8_t* bytes, size_t size);
	Utf8String(const char* cstring);
	Utf8String(const Utf8String&& v);
	~Utf8String();

	Utf8String& operator=(const Utf8String& v);
	Utf8String& operator=(Utf8String&& v);

	bool empty() const { return size_ == 0; }
	size_t size() const { return size_; }
	const uint8_t* data() const { return data_; }
	operator const char* () const { return data_; }

	const char* c_str() const { return data(); }
	std::string to_s() const { return std::string(data_, size_); }

	CharView chars();
	ByteView bytes();

private:
	void release();
	static uint8_t* dup(const uint8_t* bytes, size_t n);
};

struct Utf8String::ByteView {
	char* begin_;
	char* end_;

	ByteView(Utf8String* s) :
		begin_(s.data_),
		end_(s.data_ + s.size_)
	{}

	char* begin() { return begin_; }
	char* end() { return end_; }
};

struct Utf8String::CharView {
	Utf8String* s;

	class iterator {
		uint8_t* current;
		uint8_t* end;

		iterator& operator++();
	};

	CharView(Utf8String* _s) : s(_s) {}

	iterator begin() { return iterator({s.data(), s.data() + s.size()}); }
	iterator end() { return iterator({s.data() + s.size(), s.data() + s.size()}); }
};

inline auto Utf8String::CharView::iterator::operator++() -> iterator&
{
	// TODO

	if (current != end)
		++current;

	return *this;
}

// {{{
Utf8String::Utf8String() :
	size_(0),
	data_(nullptr)
{
}

Utf8String::Utf8String(const uint8_t* bytes, size_t size) :
	size_(size),
	data_(dup(bytes, size))
{
}

Utf8String::Utf8String(const char* cstring) :
	size_(strlen(cstring)),
	data_(dup(v.data_, size_))
{
}

Utf8String::Utf8String(const Utf8String&& v) :
	size_(v.size_),
	data_(dup(v.data_, v.size_))
{
}

Utf8String::~Utf8String()
{
	delete[] data_;
}

Utf8String& Utf8String::operator=(const Utf8String& v)
{
	return *this;
}

Utf8String& Utf8String::operator=(Utf8String&& v)
{
	release();

	data_ = v.data_;
	v.data_ = nullptr;

	size_ = v.size_;
	v.size_ = 0;

	return *this;
}

uint8_t* Utf8String::dup(const uint8_t* bytes, size_t n)
{
	uint8_t* v = new uint8_t[n + 1];
	memcpy(v, bytes, n);
	v[n] = '\0';
	return v;
}

void Utf8String::release()
{
	delete[] data_;
}
// }}}
