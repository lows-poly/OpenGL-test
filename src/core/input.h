#pragma once
#include <GLFW/glfw3.h>

struct mouse_state {
	double last_x = 0.0;
	double last_y = 0.0;
	float delta_x = 0.0f;
	float delta_y = 0.0f;
	float sensitivity = 0.2f;
	float mesh_rot_sens = 0.01f;
	bool is_pressed = false;
};

struct scroll_state {
	float delta = 0.0f;
	float speed = 2.0f;
};

const float MAX_DELTA = 60.0f;

void input_init( GLFWwindow *window_ptr, mouse_state *mouse_ptr,
                 scroll_state *scroll_ptr, mouse_state *mouse_lmb_ptr );

void input_process( GLFWwindow *window_ptr );
void input_update_rotation( mouse_state *mouse_ptr, float *rot_x, float *rot_y );
void input_get_move( GLFWwindow *window_ptr, float *fwrd_out, float *right_out );
void input_update_mesh_rotation( mouse_state *mouse_ptr, float *rot_x, float *rot_y );
