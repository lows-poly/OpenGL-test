#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct window_config {
	int width = 800;
	int height = 800;
	const char* title = "Renderer OpenGL 4.1";
};

GLFWwindow* create_window( const window_config &config );
void framebuffer_size_callback( GLFWwindow *window_ptr, int width, int height );
