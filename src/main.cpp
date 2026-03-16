#define UNUSED __attribute__((unused))

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_SIZE[2] = { 1280, 720 };
const char WINDOW_TITLE[] = "Renderer OpenGL 4.1";
const char *VERTEX_SHADER_SOURCE = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
const char *FRAGMENT_SHADER_SOURCE = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

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

	unsigned int vertexShader;
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	// glShaderSource
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

	return window;
}

void process_input( GLFWwindow *window )
{
	if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window, true );
}
