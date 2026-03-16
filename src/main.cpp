#define UNUSED __attribute__((unused))

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaders/shader_loader.h"

const int WINDOW_SIZE[2] = { 1280, 720 };
const char WINDOW_TITLE[] = "Renderer OpenGL 4.1";

std::string vertexSource = load_shader("shaders/vertex.glsl");
std::string fragmentSource = load_shader("shaders/fragment.glsl");
const char *vertexPtr = vertexSource.c_str();
const char *fragmentPtr = fragmentSource.c_str();

GLFWwindow* create_window( void );
void process_input( GLFWwindow *window );
void framebuffer_size_callback( UNUSED GLFWwindow *window, int width, int height )
{
	glViewport( 0, 0, width, height );
}

void draw_triangle( void );

// MAIN
int main (void)
{
	GLFWwindow *window = create_window();
	if ( !window ) {
		return EXIT_FAILURE;
	}

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

	glfwDestroyWindow( window );
	glfwTerminate();
	return EXIT_SUCCESS;
}

// TRIANGLE

void draw_triangle( void )
{
	// x, y ,z
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
		0.0f,   0.5f, 0.0f
	};

	// VBO = a chunk of CPU memory holding vertex data
	// VAO = remembers how to read the data
	unsigned int VBO, VAO;
	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	// create shader
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	// attach shader src to shader obj & compile
	glShaderSource( vertexShader, 1, &vertexPtr, NULL );
	glShaderSource( fragmentShader, 1, &fragmentPtr, NULL );
	glCompileShader( vertexShader );
	glCompileShader( fragmentShader );
}

// WINDOW

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

	glViewport( 0, 0, WINDOW_SIZE[0], WINDOW_SIZE[1] );
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

void process_input( GLFWwindow *window )
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window, true );
}
