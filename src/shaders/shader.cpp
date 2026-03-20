#include "shader.h"

std::string get_file_contents( const char *filename )
{
	std::ifstream in( filename, std::ios::binary );
	if (in) {
		std::string contents;
		in.seekg( 0, std::ios::end );
		contents.resize( in.tellg() );
		in.seekg( 0, std::ios::beg );
		in.read( &contents[0], contents.size() );
		in.close();
		return ( contents );
	}
	throw (errno);
}

Shader::Shader( const char *vertex_file, const char *fragment_file )
{
	std::string vertex_code = get_file_contents( vertex_file );
	std::string fragment_code = get_file_contents( fragment_file );

	const char *vertex_source = vertex_code.c_str();
	const char *fragment_source = fragment_code.c_str();

	// shaders
	GLuint vertex_shader = glCreateShader( GL_VERTEX_SHADER ); // OpenGL unsigned int
	glShaderSource( vertex_shader, 1, &vertex_source, NULL );
	glCompileShader( vertex_shader );
	this->compile_errors( vertex_shader, "VERTEX" );

	GLuint fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragment_shader, 1, &fragment_source, NULL );
	glCompileShader( fragment_shader );
	this->compile_errors( fragment_shader, "FRAGMENT" );

	// shader programme
	ID = glCreateProgram();
	glAttachShader( ID, vertex_shader );
	glAttachShader( ID, fragment_shader );
	glLinkProgram( ID );
	this->compile_errors( fragment_shader, "PROGRAM" );

	// clean up unused
	glDeleteShader( vertex_shader );
	glDeleteShader( fragment_shader );
}

void Shader::enable()
{
	glUseProgram( ID );
}

void Shader::compile_errors( unsigned int shader_id, const string& type )
{
	GLint is_compiled;
	char info_log[1024];

	if ( type != "PROGRAM" ) {
		glGetShaderiv( shader_id, GL_COMPILE_STATUS, &is_compiled );

		if ( is_compiled != GL_FALSE )
			return;

		glGetShaderInfoLog( shader_id, 1024, NULL, info_log );
		std::cerr << "SHADER_COMPILATION_ERROR: " << type << std::endl;
	} else {
		glGetProgramiv( shader_id, GL_LINK_STATUS, &is_compiled );

		if ( is_compiled != GL_FALSE )
			return;

		glGetShaderInfoLog( shader_id, 1024, NULL, info_log );
		std::cerr << "SHADER_LINKING_ERROR: " << type << std::endl;
	}
}

void Shader::destroy()
{
	glDeleteProgram( ID );
}
