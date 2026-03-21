#include "renderer.h"
#include "shaders/shader.h"

void renderer_draw( Shader *shader_ptr, Mesh *mesh_ptr, GLenum mode )
{
	shader_ptr->enable();
	shader_ptr->set_float( UNIFORM_SCALE, 1.5f );
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
