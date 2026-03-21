#pragma once

#include <vector>

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

	Mesh( float *v_ptr, size_t v_size, unsigned int *ind_ptr, size_t ind_size,
	      std::vector<Attribute> attributes );

	void bind_vao( void ) const;
	void unbind_vao( void ) const;
	unsigned int get_ind_counts( void ) const;
	void destroy_buffers( void );

private:
	GLsizei stride;
	unsigned int ind_counts;

	void setup_buffers( std::vector<Attribute> &attributes );
};
