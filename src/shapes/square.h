#pragma once

#include <glad/glad.h>

namespace shape {
	constexpr GLfloat sqre_vert[] = {
		// x    y     z        r     g     b
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
		0.5f,  -0.5f, 0.0f,    1.0f, 1.0f, 0.0f,
		0.5f,   0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 1.0f,
	};

	constexpr GLuint sqre_ind[] = {
		0, 1, 3,
		1, 2, 3
	};
}
