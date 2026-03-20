#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "window.h"

#include "renderer.h"
#include "shaders/shader.h"
#include "shaders/VAO.h"
#include "shaders/VBO.h"
#include "shaders/EBO.h"

const float TRIANGLE_SCALE = 1.0f;

GLfloat vertices[] = {
	// x    y     z        r     g     b
	0.5f,  -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
	0.0f,   0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f
};

GLuint indices[] = {
	0, 1, 2
};

GLfloat texture_coords[] = {
	0.0f, 0.0f, // lower-left corner
	1.0f, 0.0f, // lower-right corner
	0.5f, 1.0f  // top-center corner
};

int main( void )
{
	if ( !glfwInit() ) {
		std::cout << "GLFW init failed\n";
		return EXIT_FAILURE;
	}

	window_config config;
	config.width = 800;
	config.height = 800;
	config.title = "Renderer OpenGL 4.1";

	GLFWwindow *window_ptr = create_window( config );
	if ( !window_ptr )
		return EXIT_FAILURE;

	// shader
	Shader shader;

	VAO vao;
	vao.bind();

	VBO vbo( vertices, sizeof(vertices) );
	EBO ebo( indices, sizeof(indices) );

	vao.link_attributes( &vbo, 0, 3, GL_FLOAT, 6 * sizeof(float),
	                     (void*)0 );
	vao.link_attributes( &vbo, 1, 3, GL_FLOAT, 6 * sizeof(float),
	                     (void*)(3 * sizeof(float)) );

	vao.unbind();
	ebo.unbind();

	// texture
	// int img_width, img_height, num_colour_chnls;
	// unsigned char* data_ptr = stbi_load( "assets/wall.jpg", &img_width,
	//                                       &img_height, &num_colour_chnls, 0 );
	//
	// GLuint texture;
	// glGenTextures( 1, &texture );
	// glActiveTexture( GL_TEXTURES );
	// glBindTextures( GL_TEXTURE_2D, texture );
	//
	// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
	//                  GL_LINEAR_MIPMAP_LINEAR );
	// glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	//
	// if ( data_ptr ) {
	// 	glTexImage2D( GL_TEXTURES, 0, GL_RGB, img_width, img_height, 0,
	// 	              GL_RGB, GL_UNSIGNED_BYTE, data_ptr );
	//
	// 	glGenerateMipmap( GL_TEXTURE_2D );
	// } else {
	// 	std:cerr << "FAILED TO LOAD TEXTURE" << std::endl;
	// }
	// stbi_image_free( data_ptr );

	// Render Loop
	while( !glfwWindowShouldClose( window_ptr ) ) {
		// input
		window_input_process( window_ptr );

		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		renderer_draw( &shader, &vao, &ebo, GL_TRIANGLES );

		glfwSwapBuffers( window_ptr ); // update each frame
		glfwPollEvents();
	}

	renderer_destroy( &shader, &vao, &vbo, &ebo );
	// glDeleteTextures( 1, &texture );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}
