#include "mesh.h"

// Constructor

Mesh::Mesh( const GLfloat *v_ptr, size_t v_size,
            const GLuint *ind_ptr, size_t ind_size,
            std::vector<Attribute> attributes )
{
	this->ind_counts = ind_size / sizeof( GLuint );
	this->vbo = VBO( v_ptr, v_size );
	this->ebo = EBO( ind_ptr, ind_size );
	this->stride = 0;
	
	for ( auto &attr : attributes ) {
		this->stride += attr.components * sizeof( GLfloat );
	}

	this->setup_buffers( attributes );
}

// PUBLIC METHODS

void Mesh::get_transform( mat4 out ) const
{
	glm_mat4_identity( out );
	glm_translate( out, (float *)position );
	glm_rotate( out, rotation, (vec3){ 0.0f, 0.0f, 1.0f } );
	glm_scale( out, (float *)scale );
}

void Mesh::bind_vao( void ) const
{
	this->vao.bind();
}

void Mesh::unbind_vao( void ) const
{
	this->vao.unbind();
}

unsigned int Mesh::get_ind_counts( void ) const
{
	return this->ind_counts;
}

void Mesh::destroy_buffers( void )
{
	this->vao.destroy();
	this->vbo.destroy();
	this->ebo.destroy();
}

// PRIVATE METHODS

void Mesh::setup_buffers( std::vector<Attribute> &attributes )
{
	this->vao.bind();
	this->vbo.bind();
	this->ebo.bind();

	for ( auto &attr : attributes ) {
		this->vao.link_attributes( &this->vbo, attr.location,
		                           attr.components, attr.type,
		                           this->stride, (void*)attr.offset );
	}

	this->vao.unbind();
	this->vbo.unbind();
	this->ebo.unbind();
}
