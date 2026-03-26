#define UNUSED __attribute__((unused))

#include <iostream>
#include "window.h"

GLFWwindow* create_window( const window_config &config )
{
	// hints
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_SAMPLES, 8 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // macos

	GLFWwindow *window_ptr = glfwCreateWindow( config.width, config.height,
	                                           config.title, NULL, NULL );
	if ( !window_ptr ) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent( window_ptr );
	glfwSwapInterval( 1 );

	if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
		std::cerr << "Failed to initialise GLAD\n";
		return NULL;
	}

	int fb_width, fb_height;
	glfwGetFramebufferSize( window_ptr, &fb_width, &fb_height );
	glViewport( 0, 0, fb_width, fb_height );
	glfwSetFramebufferSizeCallback( window_ptr, framebuffer_size_callback );
	
	return window_ptr;
}

void framebuffer_size_callback( UNUSED GLFWwindow *window_ptr, int width, int height )
{
	glViewport( 0, 0, width, height );
}
