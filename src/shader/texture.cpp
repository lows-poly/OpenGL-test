#include <iostream>
#include <stb/stb_image.h>

#include "texture.h"

Texture::Texture( const char *path_ptr )
{
	stbi_set_flip_vertically_on_load( true );
	int width, height, num_channels;
	unsigned char *data_ptr = stbi_load( path_ptr, &width, &height,
	                                     &num_channels, 0 );

	glGenTextures( 1, &this->ID );
	glBindTexture( GL_TEXTURE_2D, this->ID );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	if ( !data_ptr ) {
		std::cerr << "FAILED TO LOAD TEXTURE: " << path_ptr << "\n";
		std::cerr << "Trying to load: " << path_ptr << "\n";
		std::cerr << "STB reason: " << stbi_failure_reason() << "\n";
		return;
	}

	GLenum format = GL_RGB;
	if ( num_channels == 4 )
		format = GL_RGBA;

	glTexImage2D( GL_TEXTURE_2D, 0, format, width, height,
	              0, format, GL_UNSIGNED_BYTE, data_ptr );
	
	glGenerateMipmap( GL_TEXTURE_2D );

	stbi_image_free( data_ptr );
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::bind( GLuint slot ) const
{
	glActiveTexture( GL_TEXTURE0 + slot );
	glBindTexture( GL_TEXTURE_2D, this->ID );
}

void Texture::unbind( void ) const
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::destroy( void )
{
	glDeleteTextures( 1, &this->ID );
}
