#pragma once

#include <vector>
#include <cglm/cglm.h>

#include "shaders/VAO.h"
#include "shaders/VBO.h"
#include "shaders/EBO.h"

struct Attribute {
	GLuint location;
	GLint components;
	GLenum type;
	size_t offset;
};

class Mesh {
public:
	VAO vao;
	VBO vbo;
	EBO ebo;

	vec3 position = { 0.0f, 0.0f, 0.0f };
	vec3 scale = { 1.0f, 1.0f, 1.0f };
	vec3 rotation = { 0.0f, 0.0f, 0.0f };

	Mesh( const GLfloat *v_ptr, size_t v_size,
	      const GLuint *ind_ptr, size_t ind_size,
	      std::vector<Attribute> attributes );

	void get_transform( mat4 out ) const;
	void set_position( float x, float y, float z );
	void set_rotation( float x, float y, float z );
	void set_scale( float x, float y, float z );
	void set_scale_uniform( float u_scale );

	unsigned int get_ind_counts( void ) const;
	void bind_vao( void ) const;
	void unbind_vao( void ) const;
	void destroy_buffers( void );

private:
	GLsizei stride;
	unsigned int ind_counts;

	void setup_buffers( std::vector<Attribute> &attributes );
};
