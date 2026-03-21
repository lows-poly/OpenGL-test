#define UNUSED __attribute__((unused))

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "window.h"

#include "renderer.h"
#include "mesh.h"
#include "shaders/shader.h"

#include "shapes/triangle.h"
#include "shapes/square.h"

int main( void )
{
	if ( !glfwInit() ) {
		std::cerr << "GLFW init failed\n";
		return EXIT_FAILURE;
	}

	// Window
	window_config config;
	config.width = 800;
	config.height = 800;
	config.title = "Renderer OpenGL 4.1";

	GLFWwindow *window_ptr = create_window( config );
	if ( !window_ptr )
		return EXIT_FAILURE;

	// Shader
	Shader shader;

	// Mesh
	Mesh mesh( shape::sqre_vert, sizeof( shape::sqre_vert ),
	           shape::sqre_ind, sizeof( shape::sqre_ind ),
	           // position
	           // colour
	           {
	                   { 0, 3, GL_FLOAT, 0 },
	                   { 1, 3, GL_FLOAT, 3 * sizeof( float ) }
	           }
	);

	// Culliing
	// glEnable( GL_CULL_FACE );
	// glCullFace( GL_BACK );
	// glFrontFace( GL_CCW );

	// Render Loop
	while( !glfwWindowShouldClose( window_ptr ) ) {
		// input
		window_input_process( window_ptr );

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		// scale oscillation
		// base + amp * sin( time )
		// smallest: base - amp;
		// biggest: base + amp;
		float time = (float) glfwGetTime();
		UNUSED float scale = 1.0f + 0.5f * sinf( time );

		mesh.set_rotation( 0.0f, time * 0.5f, 0.0f );
		// mesh.set_scale_uniform( scale * 0.5 );
		renderer_draw( &shader, &mesh, GL_TRIANGLES );

		glfwSwapBuffers( window_ptr ); // update each frame
		glfwPollEvents();
	}

	// Clean up
	renderer_destroy( &shader, &mesh );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}
