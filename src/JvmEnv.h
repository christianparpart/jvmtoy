#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Class;

class JvmEnv {
private:
	std::vector<std::string> classpaths_;
	std::unordered_map<std::string, Class*> classes_;

public:
	JvmEnv();
	~JvmEnv();

	void addClassPath(const std::string& path);

	/**
	 * \param className fully qualified class name, i.e. "java/lang/Object".
	 */
	Class* getClass(const std::string& className);
};
