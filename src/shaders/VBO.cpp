#include "VBO.h"

VBO::VBO( GLfloat *v_ptr, GLsizeiptr size )
{
	glGenBuffers( 1, &ID );
	glBindBuffer( GL_ARRAY_BUFFER, ID );
	glBufferData( GL_ARRAY_BUFFER, size, v_ptr, GL_STATIC_DRAW );
}

void VBO::bind( void )
{
	glBindBuffer( GL_ARRAY_BUFFER, ID );
}

void VBO::unbind( void )
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void VBO::destroy( void )
{
	glDeleteBuffers( 1, &ID );
}
