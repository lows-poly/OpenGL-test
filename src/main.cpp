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
#include "scene/shapes/light_cube.h"

int main( void )
{
	if ( !glfwInit() ) {
		std::cerr << "GLFW init failed\n";
		return EXIT_FAILURE;
	}

	// Window
	window_config config;
	config.width = 600;
	config.height = 600;
	config.title = "Renderer OpenGL 4.1";

	GLFWwindow *window_ptr = create_window( config );
	if ( !window_ptr )
		return EXIT_FAILURE;

	// Camera
	Camera camera;
	
	// Object
	shape_data object = shape::cube();
	shape_data light_cube = shape::light_cube();

	// Shader
	Shader shader( object.fragment_type );

	Shader light_shader( light_cube.fragment_type );

	// Mesh
	Mesh mesh( object );
	mesh.set_position( 0.0f, 0.0f, -5.0f );
	mesh.set_scale( 10.0f, 0.1f, 7.0f );

	vec3 mesh_pos;
	mesh.get_position( mesh_pos );

	Mesh light_cube_mesh( light_cube );
	light_cube_mesh.set_position( mesh_pos[0], mesh_pos[1] + 1.2f, mesh_pos[2] );
	light_cube_mesh.set_scale_uniform( 0.1f );
	
	vec3 light_pos;
	light_cube_mesh.get_position( light_pos );

	// Dept
	// glEnable( GL_DEPTH_TEST );

	// MSAA
	glEnable( GL_MULTISAMPLE );

	// Gamma
	// glEnable( GL_FRAMEBUFFER_SRGB );

	// Culling
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CCW );

	// Mouse state
	mouse_state mouse;
	mouse_state mouse_lmb;
	scroll_state scroll;
	input_init( window_ptr, &mouse, &scroll, & mouse_lmb );
	float mesh_rot_x = 0.0f;
	float mesh_rot_y = 0.0f;

	// Time
	double last_frame_time = glfwGetTime();
	float last_fps_time = last_frame_time;
	float fps = 0.0f;
	int frames = 0;

	init_imgui( window_ptr );

	// Render Loop
	while( !glfwWindowShouldClose( window_ptr ) ) {
		double current_time = glfwGetTime();
		float delta_time = (float) (current_time - last_frame_time);
		last_frame_time = current_time;
		frames++;

		// FPS counter
		if ( current_time - last_fps_time >= 1.0 ) {
			fps = frames / ( current_time - last_fps_time );

			frames = 0;
			last_fps_time = current_time;

			char title[64];
			snprintf(
				title,
				sizeof(title),
				"Renderer OpenGL 4.1 | FPS: %.2f",
				fps
			);
			glfwSetWindowTitle( window_ptr, title );
		}

		// input
		input_process( window_ptr );
		camera.update( window_ptr, delta_time, &mouse, &scroll );

		// Mesh rotation
		input_update_mesh_rotation( &mouse_lmb, &mesh_rot_x, &mesh_rot_y );
		mesh.set_rotation( mesh_rot_x, mesh_rot_y, 0.0f );

		// Clear
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello Window");
		ImGui::Text("Hello World!");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

		// Render
		renderer_draw( window_ptr, &shader, &mesh, &camera );
		shader.set_vec3( UNIFORM_VIEW_POS, camera.position[0],
		                 camera.position[1], camera.position[2] );

		shader.set_vec3( UNIFORM_LIGHT_POS, light_pos[0], light_pos[1],
		                 light_pos[2] );

		renderer_draw( window_ptr, &light_shader, &light_cube_mesh, &camera );

		glfwSwapBuffers( window_ptr );
		glfwPollEvents();
	}

	// Clean up
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	renderer_destroy( &shader, &mesh );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}
