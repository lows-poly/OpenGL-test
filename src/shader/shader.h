#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

typedef std::string string;

typedef enum {
	FRAGMENT_DEFAULT,
	FRAGMENT_TEXTURE,
	FRAGMENT_LIGHT,
	FRAGMENT_DIFFUSE,
	FRAGMENT_SOLID_DIFFUSE,
	FRAGMENT_TEXTURE_COLOUR
} FragmentType;

typedef enum {
	UNIFORM_SCALE,
	UNIFORM_COLOUR,
	UNIFORM_LIGHT,
	UNIFORM_LIGHT_POS,
	UNIFORM_VIEW_POS,
	UNIFORM_AMBIENT,
	UNIFORM_MODEL,
	UNIFORM_VIEW,
	UNIFORM_PROJECTION,
	UNIFORM_TEXTURE,
	UNIFORM_TEXTURE_SPECULAR,
	UNIFORM_TRANSFORM,
	UNIFORM_MODE,
	UNIFORM_COUNT
} Uniform;

class Shader {
public:
	GLuint ID;
	Shader( FragmentType type = FRAGMENT_DEFAULT );

	void enable( void );
	
	void bind( void );
	void cache_uniforms( void );
	void set_int( Uniform type, int value );
	void set_float( Uniform uniform, float value );
	void set_vec3( Uniform uniform, float x, float y, float z );
	void set_vec4( Uniform uniform, float x, float y, float z, float a );
	void set_mat4( Uniform uniform, const float *mat_ptr );

	void destroy( void );

private:
	GLint uniforms[UNIFORM_COUNT];

	GLuint compile_shader( GLenum type, const char *src_ptr );
	void compile_errors( unsigned int shader, const string &type );
};
