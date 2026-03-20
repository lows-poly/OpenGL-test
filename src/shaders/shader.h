#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <string>

typedef std::string string;

string get_file_contents( const char *filename );

class Shader {
	public:
		GLuint ID;
		Shader( const char *vertex_file, const char *fragment_file );

		void enable();
		void destroy();

	private:
		void compile_errors( unsigned int shader_id, const string &type );
};
