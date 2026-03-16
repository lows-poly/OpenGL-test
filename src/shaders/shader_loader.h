#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

inline std::string load_shader(const char* path)
{
	std::ifstream file(path);

	if ( !file.is_open() ) {
		std::cout << "Failed to open shader: " << path << "\n";
		return "";
	}

	std::stringstream buf;
	buf << file.rdbuf();
	return buf.str();
}
