#include "camera.h"

Camera::Camera( void )
{
	glm_vec3_copy( (vec3){ 0.0f, 0.0f, 3.0f }, position );
	glm_vec3_copy( (vec3){ 0.0f, 0.0f, 0.0f }, target );
	fov = 45.0f;
	aspect = 800.0f / 800.0f;
	near_plane = 0.1f;
	far_plane = 100.0f;
}

void Camera::get_view( mat4 out ) const
{
	vec3 up = { 0.0f, 1.0f, 0.0f };
	glm_lookat( (float *)this->position, (float *)this->target, up, out );
}

void Camera::get_projection( mat4 out ) const
{
	glm_perspective( glm_rad( this->fov ), this->aspect, this->near_plane,
	                 this->far_plane, out );
}
