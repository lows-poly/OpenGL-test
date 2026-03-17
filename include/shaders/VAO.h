#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO {
	public:
		GLuint ID;
		VAO();

		void LinkVBO( VBO *VBO_object );
		void Bind();
		void Unbind();
		void Delete();
};
