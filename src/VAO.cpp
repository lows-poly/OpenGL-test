#include "shaders/VAO.h"

VAO::VAO()
{
	glGenVertexArrays( 1, &ID );
}

void VAO::LinkVBO( VBO *VBO_object )
{
	this->Bind();
	VBO_object->Bind();

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6, (void *)0);
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6, (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray( 1 );

	VBO_object->Unbind();
	this->Unbind();
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
