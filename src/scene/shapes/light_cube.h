#pragma once

#include <glad/glad.h>
#include "shader/shader.h"
#include "scene/shapes/shape_utils.h"

namespace shape {
static constexpr GLfloat light_cube_vert[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	// left
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	// right
	0.5f,  -0.5f,  0.5f,
	0.5f,  -0.5f, -0.5f,
	0.5f,   0.5f, -0.5f,
	0.5f,   0.5f,  0.5f,
	// bottom
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	// top
	-0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
};

constexpr GLuint light_cube_ind[] = {
	// front
	0,  1,  2,   0,  2,  3,
	// back
	4,  6,  5,   4,  7,  6,
	// left
	8,  9,  10,  8,  10, 11,
	// right
	12, 13, 14,  12, 14, 15,
	// bottom
	16, 17, 18,  16, 18, 19,
	// top
	20, 21, 22,  20, 22, 23,
};

static constexpr int VERTEX_COUNT = sizeof( light_cube_vert ) / sizeof( GLfloat ) / 3;

inline shape_data light_cube( void )
{
	static const std::vector<GLfloat> verts = interleave( VERTEX_COUNT, {
		{ light_cube_vert, 3 },
	});

	return {
		verts.data(),
		light_cube_ind,
		nullptr,
		nullptr,
		verts.size() * sizeof( GLfloat ),
		sizeof( light_cube_ind ),
		{
			{ 0, 3, GL_FLOAT, 0                   },  // position
		},
		shader_type::SHADER_LIGHT_SRC,
	};
}

}
