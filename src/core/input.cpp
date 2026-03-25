#include <algorithm>
#include "input.h"

static mouse_state *g_mouse = nullptr;
static mouse_state *g_mouse_lmb = nullptr;
static scroll_state *g_scroll = nullptr;

static void cursor_callback( GLFWwindow *window_ptr, double x, double y )
{
	(void)window_ptr;

	// RMB
	if ( g_mouse && g_mouse->is_pressed ) {
		g_mouse->delta_x = (float)( x - g_mouse->last_x );
		g_mouse->delta_y = (float)( y - g_mouse->last_y );
		g_mouse->last_x = x;
		g_mouse->last_y = y;
	}
	// LMB
	if ( g_mouse_lmb && g_mouse_lmb->is_pressed ) {
		g_mouse_lmb->delta_x = (float)( x - g_mouse_lmb->last_x );
		g_mouse_lmb->delta_y = (float)( y - g_mouse_lmb->last_y );
		g_mouse_lmb->last_x = x;
		g_mouse_lmb->last_y = y;
	}
}

static void mouse_button_callback( GLFWwindow *window_ptr, int button,
                                   int action, int mods )
{
	(void)mods;
	if ( button == GLFW_MOUSE_BUTTON_RIGHT ) {
		if ( action == GLFW_PRESS ) {
			g_mouse->is_pressed = true;
			glfwGetCursorPos( window_ptr, &g_mouse->last_x,
			                  &g_mouse->last_y );

		} else if ( action == GLFW_RELEASE ) {
			g_mouse->is_pressed  = false;
			g_mouse->delta_x = 0.0f;
			g_mouse->delta_y = 0.0f;
		}
	}
	if ( button == GLFW_MOUSE_BUTTON_LEFT ) {
		if ( action == GLFW_PRESS ) {
			g_mouse_lmb->is_pressed = true;
			glfwGetCursorPos( window_ptr, &g_mouse_lmb->last_x,
			                  &g_mouse_lmb->last_y );

		} else if ( action == GLFW_RELEASE ) {
			g_mouse_lmb->is_pressed = false;
			g_mouse_lmb->delta_x = 0.0f;
			g_mouse_lmb->delta_y = 0.0f;
		}
	}
}

static void scroll_callback( GLFWwindow *window_ptr, double x_offset, double y_offset )
{
	(void)window_ptr;
	(void)x_offset;

	if ( g_scroll )
		g_scroll->delta += (float)y_offset;
}

// FUNCTIONS

void input_init( GLFWwindow *window_ptr, mouse_state *mouse_ptr,
                 scroll_state *scroll_ptr, mouse_state *mouse_lmb_ptr )
{
	g_mouse = mouse_ptr;
	g_mouse_lmb = mouse_lmb_ptr;
	g_scroll = scroll_ptr;
	glfwSetCursorPosCallback( window_ptr, cursor_callback );
	glfwSetMouseButtonCallback( window_ptr, mouse_button_callback );
	glfwSetScrollCallback( window_ptr, scroll_callback );
}

void input_process( GLFWwindow *window_ptr )
{
	if ( glfwGetKey( window_ptr, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
		glfwSetWindowShouldClose( window_ptr, true );
}

void input_update_rotation( mouse_state *mouse_ptr, float *rot_x, float *rot_y )
{
	if ( !mouse_ptr->is_pressed )
		return;

	float dx = std::clamp( mouse_ptr->delta_x, -MAX_DELTA, MAX_DELTA );
	float dy = std::clamp( mouse_ptr->delta_y, -MAX_DELTA, MAX_DELTA );

	*rot_x -= dy * mouse_ptr->sensitivity;
	*rot_y += dx * mouse_ptr->sensitivity;

	mouse_ptr->delta_x = 0.0f;
	mouse_ptr->delta_y = 0.0f;
}

void input_update_mesh_rotation( mouse_state *mouse_ptr, float *rot_x, float *rot_y )
{
	if ( !mouse_ptr->is_pressed )
		return;

	float dx = std::clamp( mouse_ptr->delta_x, -MAX_DELTA, MAX_DELTA );
	float dy = std::clamp( mouse_ptr->delta_y, -MAX_DELTA, MAX_DELTA );

	*rot_x += dy * mouse_ptr->mesh_rot_sens;
	*rot_y += dx * mouse_ptr->mesh_rot_sens;

	mouse_ptr->delta_x = 0.0f;
	mouse_ptr->delta_y = 0.0f;
}

void input_get_move( GLFWwindow *window_ptr, float *fwrd_out, float *right_out )
{
	*fwrd_out = 0.0f;
	*right_out = 0.0f;

	if ( glfwGetKey( window_ptr, GLFW_KEY_W ) == GLFW_PRESS )
		*fwrd_out += 1.0f;

	if ( glfwGetKey( window_ptr, GLFW_KEY_S ) == GLFW_PRESS )
		*fwrd_out -= 1.0f;

	if ( glfwGetKey( window_ptr, GLFW_KEY_D ) == GLFW_PRESS )
		*right_out += 1.0f;

	if ( glfwGetKey( window_ptr, GLFW_KEY_A ) == GLFW_PRESS )
		*right_out -= 1.0f;
}
