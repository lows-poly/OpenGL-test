#pragma once

#include <glad/glad.h>

class VBO {
	public:
		GLuint ID;
		VBO( void ) = default;
		VBO( const GLfloat *v_ptr, GLsizeiptr size );

		void bind( void );
		void unbind( void );
		void destroy( void );
};
