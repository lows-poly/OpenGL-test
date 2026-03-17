#include "shaders/VAO.h"

VAO::VAO()
{
	glGenVertexArrays( 1, &ID );
}

void VAO::LinkAttributes( VBO *VBO_object, GLuint layout, GLuint num_components,
                          GLenum type, GLsizeiptr stride, void *offset )
{
	VBO_object->Bind();

	glVertexAttribPointer( layout, num_components, type, GL_FALSE, stride, offset );
	glEnableVertexAttribArray( layout );

	VBO_object->Unbind();
}

void VAO::Bind( void )
{
	glBindVertexArray( ID );
}

void VAO::Unbind( void )
{
	glBindVertexArray( 0 );
}

void VAO::Delete( void )
{
	glDeleteVertexArrays( 1, &ID );
}
