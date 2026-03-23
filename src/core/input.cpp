#include "input.h"

static mouse_state *g_mouse = nullptr;

static void cursor_callback( GLFWwindow *window_ptr, double x, double y )
{
	(void)window_ptr;
	if ( !g_mouse || !g_mouse->is_pressed )
		return;

	g_mouse->delta_x = (float)( x - g_mouse->last_x );
	g_mouse->delta_y = (float)( y - g_mouse->last_y );
	g_mouse->last_x = x;
	g_mouse->last_y = y;
}

static void mouse_button_callback( GLFWwindow *window_ptr, int button,
                                   int action, int mods )
{
	(void)window_ptr;
	(void)mods;
	if ( button != GLFW_MOUSE_BUTTON_LEFT )
		return;

	if ( action == GLFW_PRESS ) {
		g_mouse->is_pressed = true;
		// snapshot position so first frame has no jump
		glfwGetCursorPos( window_ptr, &g_mouse->last_x, &g_mouse->last_y );
	} else if ( action == GLFW_RELEASE ) {
		g_mouse->is_pressed = false;
		g_mouse->delta_x = 0.0f;
		g_mouse->delta_y = 0.0f;
	}
}

void input_init( GLFWwindow *window_ptr, mouse_state *mouse_ptr )
{
	g_mouse = mouse_ptr;
	glfwSetCursorPosCallback( window_ptr, cursor_callback );
	glfwSetMouseButtonCallback( window_ptr, mouse_button_callback );
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

	*rot_x += mouse_ptr->delta_y * mouse_ptr->sensitivity;
	*rot_y += mouse_ptr->delta_x * mouse_ptr->sensitivity;

	// consume delta after applying
	mouse_ptr->delta_x = 0.0f;
	mouse_ptr->delta_y = 0.0f;
}
