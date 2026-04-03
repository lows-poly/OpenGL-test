#define UNUSED __attribute__((unused))

#include <iostream>
#include "window.h"

static void framebuffer_size_callback( UNUSED GLFWwindow *window_ptr, int width,
                                        int height )
{
	glViewport( 0, 0, width, height );
}

// CONSTRUCTOR

Window::Window( int width, int height, const char *title )
{
	// Hints
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_SAMPLES, 8 ); // MultiSampling
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // macos

	GLFWwindow *window_ptr = glfwCreateWindow( width, height,
	                                           title, NULL, NULL );
	if ( !window_ptr ) {
		std::cerr << "FAILED TO CREATE GLFW WINDOW\n";
		glfwTerminate();
	}

	glfwMakeContextCurrent( window_ptr );
	glfwSwapInterval( 1 ); // V-Sync

	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
		std::cerr << "FAILED TO INITIALISE GLAD\n";
	}

	int fb_width, fb_height;
	glfwGetFramebufferSize( window_ptr, &fb_width, &fb_height );
	glViewport( 0, 0, fb_width, fb_height );
	glfwSetFramebufferSizeCallback( window_ptr, framebuffer_size_callback );
	
	this->window_ptr = window_ptr;
}

// PUBLIC METHODS

GLFWwindow *Window::get_window( void ) const
{
	return this->window_ptr;
}

void Window::init_imgui( void )
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL( this->window_ptr, true );
	ImGui_ImplOpenGL3_Init( "#version 410" );
}

void Window::show_fps( float *dt_ptr )
{
	double current_time = glfwGetTime();
	*dt_ptr = (float) ( current_time - this->last_frame_time );
	this->last_frame_time = current_time;
	this->frames++;

	if ( current_time - this->last_fps_time >= 1.0 ) {
		this->fps = this->frames / ( current_time - this->last_fps_time );
		this->frames = 0;
		this->last_fps_time = current_time;

		char title[64];
		snprintf( title, sizeof(title), "Renderer OpenGL 4.1 | FPS: %.2f",
		          fps );

		glfwSetWindowTitle( this->window_ptr, title );
	}
}

bool Window::get_msaa( void ) const
{
	return this->MSAA;
}

void Window::set_msaa( bool enabled )
{
	this->MSAA = enabled;

	if ( enabled )
		glEnable( GL_MULTISAMPLE );
	else
		glDisable( GL_MULTISAMPLE );
}

void Window::destroy( void )
{
	glfwDestroyWindow( this->window_ptr );
	glfwTerminate();
}
