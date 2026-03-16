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

GLFWwindow* draw_window( void );
void process_input( GLFWwindow *window );
void framebuffer_size_callback( UNUSED GLFWwindow *window, int width, int height )
{
	glViewport( 0, 0, width, height );
}

void draw_triangle( Shader *shader_program, VAO *VAO1 );
void clean_shader( Shader *shader_program, VAO *VAO1, VBO *VBO1, EBO *EBO1 );

// MAIN
int main( void )
{
	if ( !glfwInit() ) {
		std::cout << "GLFW init failed\n";
		return EXIT_FAILURE;
	}

	// version hint
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // macos

	GLFWwindow *window = draw_window();
	if ( !window )
		return EXIT_FAILURE;

	// shader
	Shader shader_program( "include/shaders/default.vert.txt",
			       "include/shaders/default.frag.txt" );

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1( vertices, sizeof(vertices) );
	EBO EBO1( indices, sizeof(indices) );

	VAO1.LinkVBO( VBO1, 0 );
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Render Loop
	while( !glfwWindowShouldClose(window) ) {
		// input
		process_input( window );

		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		draw_triangle( &shader_program, &VAO1 );

		glfwSwapBuffers( window ); // update each frame
		glfwPollEvents();
	}

	clean_shader( &shader_program, &VAO1, &VBO1, &EBO1 );
	glfwDestroyWindow( window ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}

// DRAW TRIANGLE
void draw_triangle( Shader *shader_program, VAO *VAO1 )
{
	shader_program->Activate();
	VAO1->Bind();

	// mode, count, type, indices
	glDrawElements( GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0 );

	// primitive type, starting index, amount of vertices
	// glDrawArrays( GL_TRIANGLES, 0, 3);
}

void clean_shader( Shader *shader_program, VAO *VAO1, VBO *VBO1, EBO *EBO1 )
{
	VAO1->Delete();
	VBO1->Delete();
	EBO1->Delete();
	shader_program->Delete();
}

// WINDOW

GLFWwindow* draw_window( void )
{
	GLFWwindow *window = glfwCreateWindow( WINDOW_SIZE[0], WINDOW_SIZE[1],
					       WINDOW_TITLE, NULL, NULL );
	if ( !window ) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent( window );
	glfwSwapInterval(1);

	if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress )) {
		std::cout << "Failed to initialise GLAD\n";
		return NULL;
	}

	gladLoadGL();

	glViewport( 0, 0, WINDOW_SIZE[0], WINDOW_SIZE[1] );
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

void process_input( GLFWwindow *window )
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window, true );
}
