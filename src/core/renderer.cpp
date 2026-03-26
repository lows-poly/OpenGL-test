#include <cglm/cglm.h>

#include "renderer.h"

void renderer_draw( GLFWwindow *window_ptr, Shader *shader_ptr, Mesh *mesh_ptr,
                    Camera *cam_ptr, GLenum mode )
{
	int width, height;
	glfwGetFramebufferSize( window_ptr, &width, &height );

	mat4 view, projection;
	cam_ptr->get_view( view );
	cam_ptr->get_projection( projection, (float)width, (float)height );

	mesh_ptr->draw( shader_ptr, view, projection, mode );
}

void renderer_destroy( Shader *shader_ptr, Mesh *mesh_ptr )
{
	mesh_ptr->destroy_buffers();
	shader_ptr->destroy();
}
