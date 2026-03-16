#include "shaders/shader.h"

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

	GLuint fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragment_shader, 1, &fragment_source, NULL );
	glCompileShader( fragment_shader );

	// shader programme
	ID = glCreateProgram();
	glAttachShader( ID, vertex_shader );
	glAttachShader( ID, fragment_shader );
	glLinkProgram( ID );

	// clean up unused
	glDeleteShader( vertex_shader );
	glDeleteShader( fragment_shader );
}

void Shader::Activate()
{
	glUseProgram( ID );
}

void Shader::Delete()
{
	glDeleteProgram( ID );
}
