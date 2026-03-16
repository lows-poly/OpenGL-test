#define UNUSED __attribute__((unused))

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char WINDOW_TITLE[] = "Renderer OpenGL 4.1";
const int WINDOW_SIZE[2] = { 1280, 720 };

// Window resizing
void framebuffer_size_callback( UNUSED GLFWwindow *window, int width, int height )
{
	glViewport( 0, 0, width, height );
}

// Create window
GLFWwindow* create_window( void )
{
	if ( !glfwInit() ) {
		std::cout << "GLFW init failed\n";
		return NULL;
	}

	// OpenGL Version Hints
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // macos

	GLFWwindow *window = glfwCreateWindow( WINDOW_SIZE[0], WINDOW_SIZE[1],
					      WINDOW_TITLE, NULL, NULL );
	if ( !window ) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent( window );
	glfwSwapInterval(1);

	if ( !gladLoadGLLoader(( GLADloadproc ) glfwGetProcAddress )) {
		std::cout << "Failed to initialise GLAD\n";
		return NULL;
	}

	return window;
}

void process_input( GLFWwindow *window )
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window, true );
}

// Triangle

void draw_triangle( void )
{
	// x, y ,z
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
		0.0f,   0.5f, 0.0f
	};

	
}

// MAIN
int main (void)
{
	GLFWwindow *window = create_window();
	if ( !window ) {
		return EXIT_FAILURE;
	}

	glViewport( 0, 0, WINDOW_SIZE[0], WINDOW_SIZE[1] );
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Render Loop
	while( !glfwWindowShouldClose( window ) ) {
		// input
		process_input( window );

		// commands

		// clean
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
