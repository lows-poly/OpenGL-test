#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

typedef std::string string;

typedef enum {
	UNIFORM_SCALE,
	UNIFORM_COLOUR,
	UNIFORM_MODEL,
	UNIFORM_VIEW,
	UNIFORM_PROJECTION,
	UNIFORM_TEXTURE,
	UNIFORM_TRANSFORM,
	UNIFORM_COUNT
} Uniform;

class Shader {
public:
	GLuint ID;
	Shader( void );

	void enable( void );
	
	void bind( void );
	void cache_uniforms( void );
	void set_int( Uniform type, int value );
	void set_float( Uniform uniform, float value );
	void set_vec3( Uniform uniform, float x, float y, float z );
	void set_mat4( Uniform uniform, const float *mat_ptr );

	void destroy( void );

private:
	GLint uniforms[UNIFORM_COUNT];

	GLuint compile_shader( GLenum type, const char *src_ptr );
	void compile_errors( unsigned int shader, const string &type );
};
