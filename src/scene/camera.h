#pragma once
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <core/input.h>

class Camera {
public:
	vec3 position;
	float fov;
	float aspect;
	float near_plane;
	float far_plane;
	float yaw;
	float pitch;
	float move_speed = 5.0f;

	Camera( void );
	void update( GLFWwindow *window_ptr, float dt, mouse_state *mouse_ptr,
	             scroll_state *scroll_ptr );

	void get_view( mat4 out ) const;
	void get_projection( mat4 out ) const;

private:
	void get_forward( vec3 out ) const;
	void get_right( vec3 out ) const;
};
