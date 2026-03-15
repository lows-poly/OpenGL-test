#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char WINDOW_TITLE[] = "Renderer OpenGL 4.1";
const int WINDOW_SIZE[2] = { 1280, 720 };

void create_window(void)
{
	if ( !glfwInit() ) {
		std::cout << "GLFW inita failed\n";
	}

	// OpenGL Version Hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS Required

	GLFWwindow *window = glfwCreateWindow(WINDOW_SIZE[0], WINDOW_SIZE[1],
					      WINDOW_TITLE, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window\n";

		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD\n";

		return;
	}

	glViewport(0, 0, 1280, 720);

	// Render Loop
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main (void)
{
	create_window();

	glfwTerminate();
	return 0;
}
