#define UNUSED __attribute__((unused))

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WINDOW_SIZE[2] = { 1280, 720 };
const char WINDOW_TITLE[] = "Renderer OpenGL 4.1";

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

GLFWwindow* draw_window( void );
void process_input( GLFWwindow *window );
void framebuffer_size_callback( UNUSED GLFWwindow *window, int width, int height )
{
	glViewport( 0, 0, width, height );
}

// void draw_triangle( void );

// MAIN
int main (void)
{
	GLFWwindow *window = draw_window();
	if ( !window )
		return EXIT_FAILURE;

	// z, y, z
	GLfloat vertices[] = {
		-0.5f, -0.5f * float( sqrt(3) ) / 3, 0.0f,
		0.5f, -0.5f * float( sqrt(3) ) /3, 0.0f,
		0.0f, 0.5f * float( sqrt(3) ) * 2 / 3, 0.0f
	};

	// shaders
	GLuint vertex_shader = glCreateShader( GL_VERTEX_SHADER ); // OpenGL unsigned int
	glShaderSource( vertex_shader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertex_shader );

	GLuint fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragment_shader, 1, &fragmentShaderSource, NULL );
	glCompileShader( fragment_shader );

	// shader programme
	GLuint shader_program = glCreateProgram();
	glAttachShader( shader_program, vertex_shader );
	glAttachShader( shader_program, fragment_shader );
	glLinkProgram( shader_program );

	glDeleteShader( vertex_shader );
	glDeleteShader( fragment_shader );

	GLuint VAO, VBO;
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );

	glBindVertexArray( VAO );

	glBindBuffer( GL_ARRAY_BUFFER, VBO );

	// STREAM = vertices modify once and used a few times
	// STATIC = vertices modify once and used many times
	// DYNAMIC = vertices modify multiple times and used many times
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	// pos, values/vertex, ...
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindVertexArray( 0 );

	glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
	glfwSwapBuffers( window );

	// Render Loop
	while( !glfwWindowShouldClose( window ) ) {
		// input
		process_input( window );

		glClearColor( 0.07f, 0.13f, 0.17f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram( shader_program );
		glBindVertexArray( VAO );
		// primitive type, starting index, amount of vertices
		glDrawArrays( GL_TRIANGLES, 0 , 3 ); 

		glfwSwapBuffers( window ); // update each frame
		glfwPollEvents();
	}

	glDeleteVertexArrays( 1, &VAO );
	glDeleteBuffers( 1, &VBO );
	glDeleteProgram( shader_program );

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

// Triangle

// void draw_triangle( void )
// {
// 	// x, y ,z
// 	GLfloat vertices[] = {
// 		-0.5f, -0.5f * float( sqrt(3) ) / 3, 0.0f,
// 		0.5f, -0.5f * float( sqrt(3) ) /3, 0.0f,
// 		0.0f, 0.5f 8 float( sqrt(3) ) * 2 / 3, 0.0f
// 	};
//
// 	// shaders
// 	GLuint vertex_shader = glCreateShader( GL_VERTEX_SHADER ); // OpenGL unsigned int
// 	glShaderSource( vertex_shader, 1, &vertexShaderSource, NULL );
// 	glCompileShader( vertex_shader );
//
// 	GLuint fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
// 	glShaderSource( fragment_shader, 1, &fragmentShaderSource, NULL );
// 	glCompileShader( fragment_shader );
//
// 	// shader programme
// 	GLuint shader_program = glCreateProgram();
// 	glAttachShader( shader_program, vertex_shader );
// 	glAttachShader(  shader_program, fragment_shader );
// 	glLinkProgram( shader_program );
//
// 	glDeleteShader( vertex_shader );
// 	glDeleteShader( fragment_shader );
//
// 	GLuint VAO, VBO;
// 	glGenVertexArrays( 1, &VAO );
// 	glGenBuffers( 1, &VBO );
//
// 	glBindVertexArrays( VAO );
//
// 	glBindBuffer( GL_ARRAY_BUFFER, VBO );
//
// 	// STREAM = vertices modify once and used a few times
// 	// STATIC = vertices modify once and used many times
// 	// DYNAMIC = vertices modify multiple times and used many times
// 	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
//
// 	// pos, values/vertex, ...
// 	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
// 	glEnableVertexAttribArray( 0 );
//
// 	glBindBuffer( GL_ARRAY_BUFFER, 0 );
// 	glBindVertexArrays( 0 );
// }
//
