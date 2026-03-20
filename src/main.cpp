#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

#include "renderer.h"
#include "shaders/shader.h"
#include "shaders/VAO.h"
#include "shaders/VBO.h"
#include "shaders/EBO.h"

const float TRIANGLE_SCALE = 1.0f;

GLfloat vertices[] = {
	// x    y     z       r     g     b
	0.5f,  -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
	0.0f,   0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f
};

GLuint indices[] = {
	0, 1, 2
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
	Shader shader( "src/shaders/default.vert.txt",
	               "src/shaders/default.frag.txt" );

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

	GLuint uniform_id = glGetUniformLocation( shader.ID, "scale" );

	// Render Loop
	while( !glfwWindowShouldClose( window_ptr ) ) {
		// input
		window_input_process( window_ptr );

		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		renderer_draw( &shader, &vao, &ebo, uniform_id, TRIANGLE_SCALE,
		               GL_TRIANGLES );

		glfwSwapBuffers( window_ptr ); // update each frame
		glfwPollEvents();
	}

	renderer_destroy( &shader, &vao, &vbo, &ebo );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}
