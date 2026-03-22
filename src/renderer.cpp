#include <cglm/cglm.h>

#include "renderer.h"
#include "mesh.h"
#include "camera.h"
#include "shaders/shader.h"

void renderer_draw( Shader *shader_ptr, Mesh *mesh_ptr, Camera *cam_ptr,
                    Texture *tex_ptr, GLenum mode )
{
	mat4 model, view, projection;
	mesh_ptr->get_transform( model );
	cam_ptr->get_view( view );
	cam_ptr->get_projection( projection );

	shader_ptr->enable();
	shader_ptr->set_mat4( UNIFORM_MODEL, (float *)model );
	shader_ptr->set_mat4( UNIFORM_VIEW, (float *)view );
	shader_ptr->set_mat4( UNIFORM_PROJECTION, (float *)projection );

	shader_ptr->set_int( UNIFORM_TEXTURE, 0 );
	tex_ptr->bind();
	
	mesh_ptr->bind_vao();

	// draw mode, count, type, indices
	glDrawElements( mode, mesh_ptr->get_ind_counts(), GL_UNSIGNED_INT, 0 );
	mesh_ptr->unbind_vao();
}

void renderer_destroy( Shader *shader_ptr, Mesh *mesh_ptr, Texture *tex_ptr )
{
	mesh_ptr->destroy_buffers();
	shader_ptr->destroy();
	tex_ptr->destroy();
}
