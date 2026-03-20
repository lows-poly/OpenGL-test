#include "renderer.h"
#include "shaders/shader.h"

void renderer_draw( Shader *shader_ptr, VAO *vao_ptr, EBO *ebo_ptr, GLenum mode)
{
	shader_ptr->enable();
	shader_ptr->set_float( UNIFORM_SCALE, 1.5f );
	vao_ptr->bind();

	// draw mode, count, type, indices
	glDrawElements( mode, ebo_ptr->count, GL_UNSIGNED_INT, 0 );
}

void renderer_destroy( Shader *shader_ptr, VAO *vao_ptr, VBO *vbo_ptr, EBO *ebo_ptr )
{
	vao_ptr->destroy();
	vbo_ptr->destroy();
	ebo_ptr->destroy();
	shader_ptr->destroy();
}
