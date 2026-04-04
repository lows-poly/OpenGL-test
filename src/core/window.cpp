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

	this->window_ptr = glfwCreateWindow( width, height,
	                                           title, NULL, NULL );
	if ( !this->window_ptr ) {
		std::cerr << "FAILED TO CREATE GLFW WINDOW\n";
		glfwTerminate();
	}

	glfwMakeContextCurrent( this->window_ptr );
	glfwSwapInterval( 1 ); // V-Sync

	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
		std::cerr << "FAILED TO INITIALISE GLAD\n";
	}

	int fb_width, fb_height;
	glfwGetFramebufferSize( this->window_ptr, &fb_width, &fb_height );
	glViewport( 0, 0, fb_width, fb_height );
	glfwSetFramebufferSizeCallback( this->window_ptr, framebuffer_size_callback );
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
	this->io_ptr = &ImGui::GetIO();

	ImGuiStyle &style = ImGui::GetStyle();
	style.WindowRounding = 5.0f;
	style.FrameRounding  = 3.0f;

	ImGui_ImplGlfw_InitForOpenGL( this->window_ptr, true );
	ImGui_ImplOpenGL3_Init( "#version 410" );
}

void Window::start_imgui( void ) const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::create_msaa_debug( void )
{
	ImGui::Begin("DEBUG");
	ImGui::Checkbox( "MSAA", &this->MSAA );

	if ( this->MSAA )
		glEnable( GL_MULTISAMPLE );
	else
		glDisable( GL_MULTISAMPLE );

	ImGui::End();
}

void Window::render_imgui( void ) const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
}

ImGuiIO *Window::get_io( void ) const
{
	return this->io_ptr;
}

void Window::show_fps( void )
{
	if ( not this->io_ptr )
		return;

	ImGui::Text( "FPS: %.1f", this->io_ptr->Framerate );
}

// bool Window::get_msaa( void ) const
// {
// 	return this->MSAA;
// }
//
// void Window::set_msaa( bool enabled )
// {
// 	this->MSAA = enabled;
//
// 	if ( enabled )
// 		glEnable( GL_MULTISAMPLE );
// 	else
// 		glDisable( GL_MULTISAMPLE );
// }

void Window::destroy( void )
{
	glfwDestroyWindow( this->window_ptr );
	glfwTerminate();
}
