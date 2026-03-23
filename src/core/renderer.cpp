#include <cglm/cglm.h>

#include "renderer.h"
#include "scene/mesh.h"
#include "scene/camera.h"
#include "shader/shader.h"

void renderer_draw( Shader *shader_ptr, Mesh *mesh_ptr, Camera *cam_ptr,
                    GLenum mode )
{
	mat4 view, projection;
	cam_ptr->get_view( view );
	cam_ptr->get_projection( projection );

	mesh_ptr->draw( shader_ptr, view, projection, mode );
}

void renderer_destroy( Shader *shader_ptr, Mesh *mesh_ptr )
{
	mesh_ptr->destroy_buffers();
	shader_ptr->destroy();
}
