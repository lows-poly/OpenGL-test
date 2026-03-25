#pragma once

#include <glad/glad.h>
#include "shader/shader.h"
#include "scene/shapes/shape_utils.h"

namespace shape {
static constexpr GLfloat cube_vert[] = {
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

static constexpr GLfloat cube_colour[] = {
	// front   — red
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	// back    — green
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	// left    — blue
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	// right   — yellow
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	// bottom  — magenta
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	// top     — cyan
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
};

static constexpr GLfloat cube_uv[] = {
	// front
	0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
	// back
	1.0f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
	// left
	0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
	// back
	0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
	// bottom
	0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
	// top
	0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
};

constexpr GLuint cube_ind[] = {
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

static constexpr int CUBE_VERTEX_COUNT = sizeof( cube_vert ) / sizeof( GLfloat ) / 3;
static constexpr const char *TEXTURE = "assets/textures/CONCRETE-1.png";

inline shape_data cube( void )
{
	static const std::vector<GLfloat> verts = interleave( CUBE_VERTEX_COUNT, {
		{ cube_vert, 3 },
		{ cube_colour, 4 },
		{ cube_uv, 2 },
	});

	return {
		verts.data(), verts.size() * sizeof( GLfloat ),
		cube_ind, sizeof( cube_ind ),
		{
			{ 0, 3, GL_FLOAT, 0                   },  // position
			{ 1, 4, GL_FLOAT, 3 * sizeof( float ) },  // colour
			{ 2, 2, GL_FLOAT, 7 * sizeof( float ) },  // texture
		},
		FragmentType::FRAGMENT_TEXTURE,
		TEXTURE
	};
}

}
