#pragma once
#include <cglm/cglm.h>

class Camera {
public:
	vec3 position;
	vec3 target;
	float fov;
	float aspect;
	float near_plane;
	float far_plane;

	Camera( void );
	void get_view( mat4 out ) const;
	void get_projection( mat4 out ) const;
};
