#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO {
	public:
		GLuint ID;
		VAO( void );

		void link_attributes( VBO *vbo_ptr, GLuint layout,
		                      GLuint num_components, GLenum type,
		                      GLsizeiptr stride, void *offset );
		void bind( void ) const;
		void unbind( void ) const;
		void destroy( void );
};
