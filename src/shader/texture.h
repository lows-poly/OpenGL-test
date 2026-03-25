#pragma once

#include <glad/glad.h>

class Texture {
public:
	GLuint ID;

	Texture( const char *path_ptr );
	void bind( GLuint slot ) const;
	void unbind( void ) const;
	void destroy( void );
};
