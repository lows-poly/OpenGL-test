#include <cglm/cglm.h>

#include "renderer.h"
#include "mesh.h"
#include "shaders/shader.h"

void renderer_draw( Shader *shader_ptr, Mesh *mesh_ptr, GLenum mode )
{
	mat4 transform;
	mesh_ptr->get_transform( transform );

	shader_ptr->enable();
	shader_ptr->set_mat4( UNIFORM_TRANSFORM, (float *)transform );
	mesh_ptr->bind_vao();

	// draw mode, count, type, indices
	glDrawElements( mode, mesh_ptr->get_ind_counts(), GL_UNSIGNED_INT, 0 );
	mesh_ptr->unbind_vao();
}

void renderer_destroy( Shader *shader_ptr, Mesh *mesh_ptr )
{
	mesh_ptr->destroy_buffers();
	shader_ptr->destroy();
}
