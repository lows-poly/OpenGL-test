#define UNUSED __attribute__((unused))

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaders/shader.h"
#include "shaders/VAO.h"
#include "shaders/VBO.h"
#include "shaders/EBO.h"

const int WINDOW_SIZE[2] = { 1280, 720 };
const char WINDOW_TITLE[] = "Renderer OpenGL 4.1";

GLFWwindow* draw_window( void );
void process_input( GLFWwindow *window );
void framebuffer_size_callback( UNUSED GLFWwindow *window, int width, int height )
{
	glViewport( 0, 0, width, height );
}

// MAIN
int main( void )
{
	GLFWwindow *window = draw_window();
	if ( !window )
		return EXIT_FAILURE;

	// z, y, z
	GLfloat vertices[] = {
		-0.5f, -0.5f * float( sqrt(3) ) / 3, 0.0f,	// lower left corner
		0.5f, -0.5f * float( sqrt(3) ) /3, 0.0f,	// lower right corner
		0.0f, 0.5f * float( sqrt(3) ) * 2 / 3, 0.0f,	// upper corner
		-0.5f / 2, 0.5f * float( sqrt(3) ) / 6, 0.0f,	// inner left
		0.5f / 2, 0.5f * float( sqrt(3) ) /6, 0.0f,	// inner right
		0.0f, -0.5f * float( sqrt(3) ) / 3, 0.0f,	// inner down
	};

	GLuint indices[] = {
		0, 3, 5, // lower left
		3, 2, 4, // lower right
		5, 4, 1  // upper centre
	};

	// shader
	Shader shader_program( "default.vert", "default.frag" );

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1( vertices, sizeof(vertices) );
	EBO EBO1( indices, sizeof(indices) );

	VAO1.LinkVBO( VBO1, 0 );
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// clear window
	glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	glfwSwapBuffers( window );

	// Render Loop
	while( !glfwWindowShouldClose( window ) ) {
		// input
		process_input( window );

		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		shader_program.Activate();
		VAO1.Bind();
		// primitive type, starting index, amount of vertices
		glDrawElements( GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0 );

		glfwSwapBuffers( window ); // update each frame
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader_program.Delete();

	glfwDestroyWindow( window ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}

// WINDOW

GLFWwindow* draw_window( void )
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
