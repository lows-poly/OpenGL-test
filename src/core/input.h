#pragma once
#include <GLFW/glfw3.h>

struct mouse_state {
	double last_x = 0.0;
	double last_y = 0.0;
	float delta_x = 0.0f;
	float delta_y = 0.0f;
	bool is_pressed = false;
	float sensitivity = 0.005f;
};

void input_init( GLFWwindow *window_ptr, mouse_state *mouse_ptr );
void input_process( GLFWwindow *window_ptr );
void input_update_rotation( mouse_state *mouse_ptr, float *rot_x, float *rot_y );
