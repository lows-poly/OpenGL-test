#include "camera.h"

Camera::Camera( void )
{
	glm_vec3_copy( (vec3){ 0.0f, 0.0f, 3.0f }, position );
	fov = 70.0f;
	yaw = -90.0f;
	pitch = 0.0f;
	aspect = 800.0f / 800.0f;
	near_plane = 0.1f;
	far_plane = 100.0f;
}

void Camera::update( GLFWwindow *window_ptr, float dt, mouse_state *mouse_ptr,
                     scroll_state *scroll_ptr )
{
	input_update_rotation( mouse_ptr, &this->pitch, &this->yaw );
	this->pitch = glm_clamp( this->pitch, -89.0f, 89.0f );

	float fwrd_axis, right_axis;
	input_get_move( window_ptr, &fwrd_axis, &right_axis );

	vec3 forward, right;
	this->get_forward( forward );
	this->get_right( right );

	vec3 move = { 0.0f, 0.0f, 0.0f };
	glm_vec3_muladds( forward, fwrd_axis * move_speed * dt, move );
	glm_vec3_muladds( right, right_axis * move_speed * dt, move );
	glm_vec3_add( this->position, move, this->position );

	if ( scroll_ptr->delta != 0.0f ) {
		this->fov -= scroll_ptr->delta * scroll_ptr->speed;
		this->fov = glm_clamp( this->fov, 1.0f, 90.0f );
		scroll_ptr->delta = 0.0f;
	}
}

void Camera::get_view( mat4 out ) const
{
	vec3 forward, target;
	get_forward( forward );
	glm_vec3_add( (float *)this->position, forward, target );
	vec3 up = { 0.0f, 1.0f, 0.0f };
	glm_lookat( (float *)this->position, target, up, out );
}

void Camera::get_projection( mat4 out ) const
{
	glm_perspective( glm_rad( this->fov ), this->aspect, this->near_plane,
	                 this->far_plane, out );
}

// PRIVATE METHODS

void Camera::get_forward( vec3 out ) const
{
	float rad_yaw = glm_rad( this->yaw );
	float rad_pitch = glm_rad( this->pitch );

	out[0] = cosf( rad_yaw) * cosf( rad_pitch );
	out[1] = sinf( rad_pitch );
	out[2] = sinf( rad_yaw ) * cosf( rad_pitch );

	glm_vec3_normalize( out );
}

void Camera::get_right( vec3 out ) const
{
	vec4 forward, up = { 0.0f, 1.0f, 0.0f };
	get_forward( forward );
	glm_vec3_cross( forward, up, out );
	glm_vec3_normalize( out );
}
