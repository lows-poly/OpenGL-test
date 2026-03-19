#include "EBO.h"

EBO::EBO( const GLuint *indices_ptr, GLsizeiptr size )
{
	this->count = size / sizeof( GLuint );

	glGenBuffers( 1, &ID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, indices_ptr, GL_STATIC_DRAW );
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
