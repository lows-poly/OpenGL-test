#pragma once

#include <glad/glad.h>

class VBO {
	public:
		GLuint ID;
		VBO( GLfloat *vertices_ptr, GLsizeiptr size );

		void bind();
		void unbind();
		void destroy();
};
