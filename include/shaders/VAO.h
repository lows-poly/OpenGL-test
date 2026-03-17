#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO {
	public:
		GLuint ID;
		VAO();

		void LinkAttributes( VBO *VBO_object, GLuint layout,
				GLuint num_components, GLenum type,
				GLsizeiptr stride, void *offset );
		void Bind();
		void Unbind();
		void Delete();
};
