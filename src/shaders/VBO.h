#pragma once

#include <glad/glad.h>

class VBO {
	public:
		GLuint ID;
		VBO( GLfloat *vertices_ptr, GLsizeiptr size );

		void bind( void );
		void unbind( void );
		void destroy( void );
};
