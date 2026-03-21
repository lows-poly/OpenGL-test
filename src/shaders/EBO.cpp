#include "EBO.h"

EBO::EBO( const GLuint *ind_ptr, GLsizeiptr size )
{
	glGenBuffers( 1, &ID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, ind_ptr, GL_STATIC_DRAW );
}

void EBO::bind( void )
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ID );
}

void EBO::unbind( void )
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void EBO::destroy( void )
{
	glDeleteBuffers( 1, &ID );
}
