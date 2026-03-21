#pragma once

#include <glad/glad.h>

class EBO {
	public:
		GLuint ID;
		EBO( void ) = default;
		EBO( const GLuint *ind_ptr, GLsizeiptr size);

		void bind( void );
		void unbind( void );
		void destroy( void );
};
