#define UNUSED __attribute__((unused))

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "core/window.h"
#include "core/input.h"
#include "core/renderer.h"

#include "scene/camera.h"
#include "scene/mesh.h"

#include "shader/shader.h"
#include "shader/texture.h"

#include "scene/shapes/triangle.h"
#include "scene/shapes/square.h"
#include "scene/shapes/cube.h"

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
	
	// Object
	shape_data object = shape::cube();

	// Shader
	Shader shader( object.fragment_type );

	// Mesh
	Mesh mesh( object );

	// Culling
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );

	// Time
	float last_time = 0.0f;
	float delta_time = 0.0f;
	int frames = 0;

	// Mouse state
	mouse_state mouse;
	input_init( window_ptr, &mouse );
	float rot_x = 0.0f;
	float rot_y = 0.0f;

	// Render Loop
	while( !glfwWindowShouldClose( window_ptr ) ) {
		// input
		input_process( window_ptr );
		input_update_rotation( &mouse, &rot_x, &rot_y );

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

		mesh.set_rotation( rot_x * 0.5f, rot_y * 0.5f, 0.0f );

		// mesh.set_scale_uniform( scale * 0.5 );
		
		renderer_draw( &shader, &mesh, &camera, GL_TRIANGLES );

		glfwSwapBuffers( window_ptr ); // update each frame
		glfwPollEvents();
	}

	// Clean up
	renderer_destroy( &shader, &mesh );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}
