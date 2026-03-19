#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

#include "shaders/shader.h"
#include "shaders/VAO.h"
#include "shaders/VBO.h"
#include "shaders/EBO.h"

const float TRIANGLE_SCALE = 1.0f;

GLfloat vertices[] = {
	// x    y     z       r     g     b
	0.5f,  -0.5f, 0.0f,   0.1f, 0.0f, 0.0f,
	0.0f,   0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   0.1f, 0.0f, 0.0f
};

GLuint indices[] = {
	0, 1, 2
};

void draw_triangle( Shader *shader_ptr, VAO *vao_ptr, GLuint uniID );
void clean_shader( Shader *shader_ptr, VAO *vao_ptr, VBO *vbo_ptr,
                   EBO *ebo_ptr );

// MAIN
int main( void )
{
	if ( !glfwInit() ) {
		std::cout << "GLFW init failed\n";
		return EXIT_FAILURE;
	}

	window_config config;
	config.width = 800;
	config.height = 800;
	config.title = "Renderer OpenGL 4.1";

	GLFWwindow *window_ptr = create_window( config );
	if ( !window_ptr )
		return EXIT_FAILURE;

	// shader
	Shader shader( "src/shaders/default.vert.txt",
	               "src/shaders/default.frag.txt" );

	VAO vao;
	vao.bind();

	VBO vbo( vertices, sizeof(vertices) );
	EBO ebo( indices, sizeof(indices) );

	vao.LinkAttributes( &vbo, 0, 3, GL_FLOAT, 6 * sizeof(float),
	                    (void*)0 );
	vao.LinkAttributes( &vbo, 1, 3, GL_FLOAT, 6 * sizeof(float),
	                    (void*)(3 * sizeof(float)) );

	vao.unbind();
	ebo.unbind();

	// uniID
	GLuint uniID = glGetUniformLocation( shader.ID, "scale" );

	// Render Loop
	while( !glfwWindowShouldClose(window_ptr) ) {
		// input
		window_input_process( window_ptr );

		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		draw_triangle( &shader, &vao, uniID );

		glfwSwapBuffers( window_ptr ); // update each frame
		glfwPollEvents();
	}

	clean_shader( &shader, &vao, &vbo, &ebo );
	glfwDestroyWindow( window_ptr ); // delete window before ending the program
	glfwTerminate(); // terminate glfw entirely
	return EXIT_SUCCESS;
}

// DRAW TRIANGLE
void draw_triangle( Shader *shader_ptr, VAO *vao_ptr, GLuint uniID )
{
	shader_ptr->enable();
	glUniform1f( uniID, TRIANGLE_SCALE );
	vao_ptr->bind();

	// mode, count, type, indices
	glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );

	// primitive type, starting index, amount of vertices
	// glDrawArrays( GL_TRIANGLES, 0, 3);
}

void clean_shader( Shader *shader_ptr, VAO *vao_ptr, VBO *vbo_ptr,
                   EBO *ebo_ptr )
{
	vao_ptr->destroy();
	vbo_ptr->destroy();
	ebo_ptr->destroy();
	shader_ptr->destroy();
}
