#pragma once

#include <stdint.h>
#include <sys/param.h>
#include <unordered_map>
#include <vector>
#include <string>

class Class;

class VMClassLoader
{
private:
	std::unordered_map<std::string, Class*> classes_;
	std::vector<std::string> classpaths_;

public:
	VMClassLoader();
	~VMClassLoader();

	void addClassPath(const std::string& path);

	Class* findLoadedClass(const char* name);
	Class* findClass(const char* name);
	Class* defineClass(const char* name, const uint8_t* classfile, size_t size);
	void resolveClass(Class* c);

	Class* loadClass(const char* name, bool resolve);
};
