#pragma once

#include <glad/glad.h>

namespace shape {
	constexpr GLfloat tri_vert[] = {
		// x    y     z        r     g     b
		0.5f,  -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
		0.0f,   0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f
	};

	constexpr GLuint tri_ind[] = {
		0, 1, 2
	};
}
