#pragma once

#include <glad/glad.h>

class EBO {
	public:
		GLuint ID;
		GLsizei count;
		EBO( const GLuint *indices_ptr, GLsizeiptr size);

		void bind( void );
		void unbind( void );
		void destroy( void );
};
