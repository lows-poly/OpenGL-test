#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window( int width = 600, int height = 600,
	        const char *title = "Renderer OpenGL 4.1" );

	GLFWwindow *get_window( void ) const;
	void init_imgui( void );
	void show_fps( float *dt_ptr );

	void destroy( void );

private:
	GLFWwindow *window_ptr;

	double last_frame_time = glfwGetTime();
	float last_fps_time = this->last_frame_time;
	float fps = 0.0f;
	int frames = 0;
};
