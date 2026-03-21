#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "window.h"

#include "renderer.h"
#include "mesh.h"
#include "shaders/shader.h"

#include "shapes/triangle.h"

int main( void )
{
	if ( !glfwInit() ) {
		std::cerr << "GLFW init failed\n";
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

	Mesh mesh( shape::tri_vert, sizeof( shape::tri_vert ),
	           shape::tri_ind, sizeof( shape::tri_ind ),
	           // position
	           // colour
	           {
	                   { 0, 3, GL_FLOAT, 0 },
	                   { 1, 3, GL_FLOAT, 3 * sizeof( float ) }
	           }
	);

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
		float scale = 1.0f + 0.5f * sinf( time );

		glm_vec3_fill( mesh.scale, scale );
		renderer_draw( &shader, &mesh, GL_TRIANGLES );

		glfwSwapBuffers( window_ptr ); // update each frame
		glfwPollEvents();
	}

	renderer_destroy( &shader, &mesh );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}
