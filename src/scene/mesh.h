#pragma once

#include <vector>
#include <optional>
#include <glad/glad.h>
#include <cglm/cglm.h>

#include "shader/shader.h"
#include "shader/texture.h"
#include "shader/buffers/VAO.h"
#include "shader/buffers/VBO.h"
#include "shader/buffers/EBO.h"

struct Attribute {
	GLuint location;
	GLint components;
	GLenum type;
	GLsizei offset;
};
struct shape_data {
	const GLfloat *v_ptr;
	const GLuint *ind_ptr;
	const char *texture_path;
	const char *texture_spec_path;
	size_t v_size;
	size_t ind_size;
	std::vector<Attribute> attributes;
	FragmentType fragment_type;
};

class Mesh {
public:
	Mesh( const shape_data &shape );

	Mesh( const GLfloat *v_ptr, size_t v_size,
	      const GLuint *ind_ptr, size_t ind_size,
	      std::vector<Attribute> attributes,
	      const char *texture_path = nullptr,
	      const char *texture_spec_path = nullptr );

	void draw( Shader *shader_ptr, mat4 view, mat4 projection, GLenum mode );
	void get_transform( mat4 out ) const;
	void get_position( vec3 out ) const;
	void set_position( float x, float y, float z );
	void set_rotation( float x, float y, float z );
	void set_scale( float x, float y, float z );
	void set_scale_uniform( float u_scale );

	void destroy_buffers( void );

private:
	GLsizei stride;
	unsigned int ind_counts;

	VAO vao;
	VBO vbo;
	EBO ebo;

	vec3 position = { 0.0f, 0.0f, 0.0f };
	vec3 scale = { 1.0f, 1.0f, 1.0f };
	vec3 rotation = { 0.0f, 0.0f, 0.0f };

	std::optional<Texture> texture;
	std::optional<Texture> texture_spec;

	void setup_buffers( std::vector<Attribute> &attributes );
};
