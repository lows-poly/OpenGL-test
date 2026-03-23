#include "mesh.h"

// Constructor

Mesh::Mesh( const shape_data &shape )
    : Mesh( shape.v_ptr, shape.v_size,
            shape.ind_ptr, shape.ind_size,
            shape.attributes, shape.texture_path )
{}

Mesh::Mesh( const GLfloat *v_ptr, size_t v_size,
            const GLuint *ind_ptr, size_t ind_size,
            std::vector<Attribute> attributes,
            const char *texture_path )
{
	this->ind_counts = ind_size / sizeof( GLuint );
	this->vbo = VBO( v_ptr, v_size );
	this->ebo = EBO( ind_ptr, ind_size );
	this->stride = 0;

	if ( texture_path )
		this->texture = Texture( texture_path );
	
	for ( auto &attr : attributes ) {
		this->stride += attr.components * sizeof( GLfloat );
	}

	this->setup_buffers( attributes );
}

// PUBLIC METHODS

void Mesh::draw( Shader *shader_ptr, mat4 view, mat4 proj, GLenum mode )
{
	mat4 model;
	this->get_transform( model );

	shader_ptr->enable();
	shader_ptr->set_mat4( UNIFORM_MODEL, (float *)model );
	shader_ptr->set_mat4( UNIFORM_VIEW, (float *)view );
	shader_ptr->set_mat4( UNIFORM_PROJECTION, (float *)proj );

	if ( this->texture.has_value() ) {
		shader_ptr->set_int( UNIFORM_TEXTURE, 0 );
		this->texture->bind();
	}
	
	this->vao.bind();
	glDrawElements( mode, this->ind_counts, GL_UNSIGNED_INT, 0 );
	this->vao.unbind();
}

void Mesh::get_transform( mat4 out ) const
{
	glm_mat4_identity( out );
	glm_translate( out, (float *)position );

	glm_rotate( out, rotation[0], (vec3){ 1.0f, 0.0f, 0.0f } );
	glm_rotate( out, rotation[1], (vec3){ 0.0f, 1.0f, 0.0f } );
	glm_rotate( out, rotation[2], (vec3){ 0.0f, 0.0f, 1.0f } );

	glm_scale( out, (float *)scale );
}

void Mesh::set_position( float x, float y, float z )
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
}

void Mesh::set_rotation( float x, float y, float z )
{
	this->rotation[0] = x;
	this->rotation[1] = y;
	this->rotation[2] = z;
}

void Mesh::set_scale( float x, float y, float z )
{
	this->scale[0] = x;
	this->scale[1] = y;
	this->scale[2] = z;
}

void Mesh::set_scale_uniform( float u_scale )
{
	glm_vec3_fill( this->scale, u_scale ); 
}

void Mesh::destroy_buffers( void )
{
	this->vao.destroy();
	this->vbo.destroy();
	this->ebo.destroy();

	if ( this->texture.has_value() )
		this->texture->destroy();
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
