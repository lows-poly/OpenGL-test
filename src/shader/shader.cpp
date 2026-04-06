#include <iostream>
#include <fstream>
#include <string>

#include "shader.h"

// FUNCTIONS

static const char *u_names[UNIFORM_COUNT] = {
	[UNIFORM_SCALE] = "scale",
	[UNIFORM_COLOUR] = "u_colour",
	[UNIFORM_LIGHT] = "u_light_colour",
	[UNIFORM_LIGHT_POS] = "u_light_pos",
	[UNIFORM_AMBIENT] = "u_ambient",
	[UNIFORM_VIEW_POS] = "u_view_pos",
	[UNIFORM_MODEL] = "u_model",
	[UNIFORM_VIEW] = "u_view",
	[UNIFORM_PROJECTION] = "u_projection",
	[UNIFORM_TEXTURE] = "u_texture",
	[UNIFORM_TEXTURE_SPECULAR] = "u_texture_specular",
	[UNIFORM_MODE] = "u_mode",
	[UNIFORM_TRANSFORM] = "u_transform"
};

static std::string read_file( const char *path_ptr )
{
	std::ifstream in( path_ptr, std::ios::binary );

	if ( !in )
		throw std::runtime_error( "FAILED TO READ FILE" );

	std::string contents;

	in.seekg( 0, std::ios::end );
	contents.resize( in.tellg() );
	in.seekg( 0, std::ios::beg );
	in.read( &contents[0], contents.size() );
	in.close();

	return ( contents );
}

// Constructor

Shader::Shader( shader_type type )
{
	std::string vertex_code = read_file( "src/shader/glsl/point.vert.glsl" );
	std::string fragment_code;

	this->get_shader( type, &vertex_code, &fragment_code );

	const char *v_src_ptr = vertex_code.c_str();
	const char *f_src_ptr = fragment_code.c_str();

	if ( !v_src_ptr || !f_src_ptr ) {
		std::cerr << "FAILED TO GET SHADER SOURCES" << std::endl;
		return;
	}

	// shaders
	GLuint vertex_shader = compile_shader( GL_VERTEX_SHADER, v_src_ptr );
	GLuint fragment_shader = compile_shader( GL_FRAGMENT_SHADER, f_src_ptr );

	// shader programme
	GLuint programme = glCreateProgram();
	glAttachShader( programme, vertex_shader );
	glAttachShader( programme, fragment_shader );
	glLinkProgram( programme );
	this->compile_errors( programme, "PROGRAM" );

	// clean up unused
	glDeleteShader( vertex_shader );
	glDeleteShader( fragment_shader );

	this->ID = programme;
	this->cache_uniforms();
}

// PUBLIC METHODS

void Shader::enable( void )
{
	glUseProgram( this->ID );
}

void Shader::set_int( Uniform type, int value )
{
	GLint loc = this->uniforms[type];
	if ( loc != -1 )
		glUniform1i( loc, value );
}

void Shader::set_float( Uniform type, float value )
{
	GLint loc = this->uniforms[type];
	if ( loc != -1 )
		glUniform1f( loc, value );
}

void Shader::set_vec3(Uniform type, float x, float y, float z)
{
	GLint loc = uniforms[type];
	if ( loc != -1 )
		glUniform3f( loc, x, y, z );
}

void Shader::set_vec4(Uniform type, float x, float y, float z, float a )
{
	GLint loc = uniforms[type];
	if ( loc != -1 )
		glUniform4f( loc, x, y, z, a );
}

void Shader::set_mat4(Uniform type, const float *mat)
{
	GLint loc = uniforms[type];
	if ( loc != -1 )
		glUniformMatrix4fv( loc, 1, GL_FALSE, mat );
}

void Shader::cache_uniforms( void )
{
	for ( int i = 0; i < UNIFORM_COUNT; i++ ) {
		this->uniforms[i] = glGetUniformLocation( this->ID, u_names[i] );
	}
}

void Shader::destroy( void )
{
	glDeleteProgram( this->ID );
}

// PRIVATE METHODS

void Shader::get_shader( shader_type type, std::string *vert_ptr,
                         std::string *frag_ptr )
{
	if ( !vert_ptr || !frag_ptr )
		return;

	switch ( type ) {
	case SHADER_POINT:
		*vert_ptr = read_file( "src/shader/glsl/point.vert.glsl" );
		*frag_ptr = read_file( "src/shader/glsl/point.frag.glsl" );
		break;
	case SHADER_SPOT:
		*vert_ptr = read_file( "src/shader/glsl/default.vert.glsl" );
		*frag_ptr = read_file( "src/shader/glsl/spotlight.frag.glsl" );
		break;
	case SHADER_DIRECTIONAL:
		*vert_ptr = read_file( "src/shader/glsl/default.vert.glsl" );
		*frag_ptr = read_file( "src/shader/glsl/spotlight.frag.glsl" );
		break;
	case SHADER_LIGHT_SRC:
		*vert_ptr = read_file( "src/shader/glsl/point.vert.glsl" );
		*frag_ptr = read_file( "src/shader/glsl/light.frag.glsl" );
		break;
	default:
		*vert_ptr = read_file( "src/shader/glsl/default.vert.glsl" );
		*frag_ptr = read_file( "src/shader/glsl/directional.frag.glsl" );
		break;
	}
}

GLuint Shader::compile_shader( GLenum type, const char *src_ptr )
{
	GLuint id = glCreateShader( type );
	glShaderSource( id, 1, &src_ptr, NULL );
	glCompileShader( id );

	switch ( type ) {
	case GL_VERTEX_SHADER:
		this->compile_errors( id, "VERTEX" );
		break;
	case GL_FRAGMENT_SHADER:
		this->compile_errors( id, "FRAGMENT" );
		break;
	default:
		std::cerr << "UNKNOWN SHADER" << std::endl;
		break;
	}

	return id;
}

void Shader::compile_errors( unsigned int shader, const std::string &type )
{
	GLint is_compiled;
	char info_log[1024];

	if ( type != "PROGRAM" ) {
		glGetShaderiv( shader, GL_COMPILE_STATUS, &is_compiled );

		if ( is_compiled != GL_FALSE )
			return;

		glGetShaderInfoLog( shader, 1024, NULL, info_log );
		std::cerr << "SHADER_COMPILATION_ERROR: " << type << "\n";
		std::cerr << info_log << type << std::endl;
	} else {
		glGetProgramiv( shader, GL_LINK_STATUS, &is_compiled );

		if ( is_compiled != GL_FALSE )
			return;

		glGetProgramInfoLog( shader, 1024, NULL, info_log );
		std::cerr << "SHADER_LINKING_ERROR: " << type << "\n";
		std::cerr << info_log << type << std::endl;
	}
}
