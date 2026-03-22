#define UNUSED __attribute__((unused))

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "window.h"

#include "renderer.h"
#include "camera.h"
#include "mesh.h"
#include "shaders/shader.h"
#include "shaders/texture.h"

#include "shapes/triangle.h"
#include "shapes/square.h"
#include "shapes/cube.h"

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

	// Camera
	Camera camera;

	glEnable( GL_DEPTH_TEST );

	// Shader
	Shader shader( FRAGMENT_TEXTURE );

	// Mesh
	Mesh mesh( shape::cube_vert, sizeof( shape::cube_vert ),
	           shape::cube_ind, sizeof( shape::cube_ind ),
	           // position
	           // colour
	           // texture
	           {
	                   { 0, 3, GL_FLOAT, 0 },
	                   { 1, 4, GL_FLOAT, 3 * sizeof( float ) },
	                   { 2, 2, GL_FLOAT, 7 * sizeof( float ) }
	           }
	);

	// Texture
	Texture texture( "assets/textures/err-texture.jpeg" );

	// Culliing
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );

	// Time
	float last_time = 0.0f;
	float delta_time = 0.0f;
	int frames = 0;

	// Render Loop
	while( !glfwWindowShouldClose( window_ptr ) ) {
		// input
		window_input_process( window_ptr );

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		float current_time = (float) glfwGetTime();
		delta_time = current_time - last_time;
		last_time = current_time;
		frames++;

		// scale oscillation
		// base + amp * sin( time )
		// smallest: base - amp;
		// biggest: base + amp;
		// float scale = 1.0f + 0.5f * sinf( time );

		if ( fmod( current_time, 1.0f ) < delta_time ) {
			std::cout << "FPS: " << frames << "\n";
			frames = 0;
		}

		mesh.set_rotation( 0.0f,
		                   current_time * 0.5f,
		                   current_time * 0.5f );

		// mesh.set_scale_uniform( scale * 0.5 );
		
		renderer_draw( &shader, &mesh, &camera, &texture, GL_TRIANGLES );

		glfwSwapBuffers( window_ptr ); // update each frame
		glfwPollEvents();
	}

	// Clean up
	renderer_destroy( &shader, &mesh, &texture );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}
