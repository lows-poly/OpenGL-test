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
	// x    y     z       r     g     b
	0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	0.0f,   0.5f, 0.0f,   0.1f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f
};

GLuint indices[] = {
	0, 2, 1
};

GLFWwindow* draw_window( void );
void process_input( GLFWwindow *window );
void framebuffer_size_callback( UNUSED GLFWwindow *window, int width, int height )
{
	glViewport( 0, 0, width, height );
}

void draw_triangle( Shader *shader_program, VAO *VAO_object );
void clean_shader( Shader *shader_program, VAO *VAO_object, VBO *VBO_object,
		   EBO *EBO_object );

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

	VAO VAO_object;

	VBO VBO_object( vertices, sizeof(vertices) );
	EBO EBO_object( indices, sizeof(indices) );

	VAO_object.LinkVBO( &VBO_object );
	EBO_object.Unbind();

	// Render Loop
	while( !glfwWindowShouldClose(window) ) {
		// input
		process_input( window );

		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		draw_triangle( &shader_program, &VAO_object );

		glfwSwapBuffers( window ); // update each frame
		glfwPollEvents();
	}

	clean_shader( &shader_program, &VAO_object, &VBO_object, &EBO_object );
	glfwDestroyWindow( window ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}

// DRAW TRIANGLE
void draw_triangle( Shader *shader_program, VAO *VAO_object )
{
	shader_program->Activate();
	VAO_object->Bind();

	// mode, count, type, indices
	// glDrawElements( GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0 );

	// primitive type, starting index, amount of vertices
	glDrawArrays( GL_TRIANGLES, 0, 3);
}

void clean_shader( Shader *shader_program, VAO *VAO_object, VBO *VBO_object,
		   EBO *EBO_object )
{
	VAO_object->Delete();
	VBO_object->Delete();
	EBO_object->Delete();
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
