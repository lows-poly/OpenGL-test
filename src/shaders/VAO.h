#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO {
	public:
		GLuint ID;
		VAO();

		void LinkAttributes( VBO *vbo_ptr, GLuint layout,
		                     GLuint num_components, GLenum type,
		                     GLsizeiptr stride, void *offset );
		void bind();
		void unbind();
		void destroy();
};
