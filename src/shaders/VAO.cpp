#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays( 1, &ID );
}

void VAO::LinkAttributes( VBO *vbo_ptr, GLuint layout, GLuint num_components,
                          GLenum type, GLsizeiptr stride, void *offset )
{
	vbo_ptr->bind();

	glVertexAttribPointer( layout, num_components, type, GL_FALSE, stride, offset );
	glEnableVertexAttribArray( layout );

	vbo_ptr->unbind();
}

void VAO::bind( void )
{
	glBindVertexArray( ID );
}

void VAO::unbind( void )
{
	glBindVertexArray( 0 );
}

void VAO::destroy( void )
{
	glDeleteVertexArrays( 1, &ID );
}
