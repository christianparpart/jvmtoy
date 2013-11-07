#pragma once

class Class;

class VMClassLoader
{
public:
	VMClassLoader();
	~VMClassLoader();

	Class* findClass(const char* name);
	Class* defineClass(const char* name, const uint8_t* classfile, size_t size);
};
