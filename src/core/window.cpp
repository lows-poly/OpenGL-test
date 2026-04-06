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
	glfwWindowHint( GLFW_SAMPLES, 32 ); // MultiSampling
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

	// Shape
	style.WindowRounding    = 0.0f;
	style.FrameRounding     = 0.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabRounding      = 0.0f;
	style.TabRounding       = 0.0f;
	style.WindowBorderSize  = 1.0f;
	style.FrameBorderSize   = 1.0f;

	// Spacing
	style.WindowPadding = ImVec2( 6.0f, 6.0f );
	style.FramePadding = ImVec2( 4.0f, 2.0f );
	style.ItemSpacing  = ImVec2( 6.0f, 4.0f );

	ImVec4 *colors = style.Colors;

	// Windows
	colors[ImGuiCol_WindowBg]     = ImVec4( 0.12f, 0.12f, 0.10f, 0.80f );
	colors[ImGuiCol_Border]       = ImVec4( 0.50f, 0.50f, 0.40f, 0.80f );
	colors[ImGuiCol_BorderShadow] = ImVec4( 0.00f, 0.00f, 0.00f, 0.80f );

	// Title
	colors[ImGuiCol_TitleBg]          = ImVec4( 0.20f, 0.18f, 0.14f, 1.00f );
	colors[ImGuiCol_TitleBgActive]    = ImVec4( 0.55f, 0.45f, 0.10f, 1.00f );
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4( 0.15f, 0.14f, 0.10f, 1.00f );

	// Frame (inputs, checkboxes)
	colors[ImGuiCol_FrameBg]        = ImVec4( 0.20f, 0.20f, 0.16f, 1.00f );
	colors[ImGuiCol_FrameBgHovered] = ImVec4( 0.35f, 0.32f, 0.20f, 1.00f );
	colors[ImGuiCol_FrameBgActive]  = ImVec4( 0.45f, 0.40f, 0.20f, 1.00f );

	// Buttons
	colors[ImGuiCol_Button]        = ImVec4( 0.30f, 0.28f, 0.18f, 1.00f );
	colors[ImGuiCol_ButtonHovered] = ImVec4( 0.55f, 0.50f, 0.20f, 1.00f );
	colors[ImGuiCol_ButtonActive]  = ImVec4( 0.70f, 0.60f, 0.10f, 1.00f );

	// Headers
	colors[ImGuiCol_Header]        = ImVec4( 0.35f, 0.30f, 0.15f, 1.00f );
	colors[ImGuiCol_HeaderHovered] = ImVec4( 0.50f, 0.44f, 0.18f, 1.00f );
	colors[ImGuiCol_HeaderActive]  = ImVec4( 0.65f, 0.55f, 0.10f, 1.00f );

	// Scrollbar
	colors[ImGuiCol_ScrollbarBg]          = ImVec4( 0.10f, 0.10f, 0.08f, 1.00f );
	colors[ImGuiCol_ScrollbarGrab]        = ImVec4( 0.40f, 0.36f, 0.20f, 1.00f );
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4( 0.55f, 0.50f, 0.25f, 1.00f );
	colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4( 0.65f, 0.58f, 0.20f, 1.00f );

	// Checkmark / slider
	colors[ImGuiCol_CheckMark]        = ImVec4( 0.90f, 0.80f, 0.30f, 1.00f );
	colors[ImGuiCol_SliderGrab]       = ImVec4( 0.60f, 0.52f, 0.20f, 1.00f );
	colors[ImGuiCol_SliderGrabActive] = ImVec4( 0.80f, 0.70f, 0.20f, 1.00f );

	// Text
	colors[ImGuiCol_Text]         = ImVec4( 0.85f, 0.85f, 0.70f, 1.00f );
	colors[ImGuiCol_TextDisabled] = ImVec4( 0.45f, 0.45f, 0.35f, 1.00f );

	ImGui_ImplGlfw_InitForOpenGL( this->window_ptr, true );
	ImGui_ImplOpenGL3_Init( "#version 410" );
}

void Window::start_imgui( void ) const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::render_imgui( void ) const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
}

void Window::create_debug_window( void )
{
	ImGui::SetNextWindowSize( ImVec2( 200.0f, 90.0f ), ImGuiCond_Always );
	ImGui::Begin("DEBUG", nullptr, ImGuiWindowFlags_NoResize );

	ImGui::Checkbox( "MSAA", &this->MSAA );
	ImGui::Checkbox( "V-SYNC", &this->V_SYNC );
	ImGui::Checkbox( "CULLING", &this->CULLING );

	if ( this->MSAA )
		glEnable( GL_MULTISAMPLE );
	else
		glDisable( GL_MULTISAMPLE );

	if ( this->V_SYNC )
		glfwSwapInterval( 1 );
	else
		glfwSwapInterval( 0 );

	if ( this->CULLING )
		glEnable( GL_CULL_FACE );
	else
		glDisable( GL_CULL_FACE );

	ImGui::End();
}

void Window::show_fps( void )
{
	if ( not this->io_ptr )
		return;

	// True FPS
	int fw, ww;
	glfwGetFramebufferSize( this->window_ptr, &fw, nullptr );
	glfwGetWindowSize( this->window_ptr, &ww, nullptr );
	float scale = (float)fw / (float)ww;
	float fps = this->io_ptr->Framerate / scale;

	// Avg FPS
	static float history[100] = {};
	static float sum = 0.0f;
	static int index = 0;
	static float timer = 0.0f;

	timer += this->io_ptr->DeltaTime;

	sum -= history[index];
	history[index] = fps;
	sum += fps;
	index = (index + 1) % 100;

	static float avg_fps = 0.0f;
	
	if ( timer >= AVG_FPS_INTERVAL ) {
		avg_fps = sum / 100;
		timer = 0.0f;
	}

	// Gui
	ImGui::SetNextWindowSize( ImVec2( 100.0f, 60.0f ), ImGuiCond_Always );
	ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoResize );
	ImGui::Text( "FPS: %.1f", fps );
	ImGui::Text( "AVG: %.1f", avg_fps );
	ImGui::End();
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

ImGuiIO *Window::get_io( void ) const
{
	return this->io_ptr;
}

void Window::destroy( void )
{
	glfwDestroyWindow( this->window_ptr );
	glfwTerminate();
}
