#pragma once

#include <vector>
#include <glad/glad.h>

namespace shape {

struct attrib_span {
	const GLfloat *data;
	int comps;
};

inline void write_attrib( std::vector<GLfloat> &out, const attrib_span &span,
                          int vertex, int stride, int offset )
{
	for ( int c = 0; c < span.comps; c++ ) {
		out[vertex * stride + offset + c] = span.data[vertex * span.comps + c];
	}
}

inline std::vector<GLfloat> interleave( int v_count,
                                        std::initializer_list<attrib_span> spans )
{
	int stride = 0;
	for ( auto &span : spans ) {
		stride += span.comps;
	}

	std::vector<GLfloat> out( v_count * stride );

	for ( int v = 0; v < v_count; v++ ) {
		int offset = 0;

		for ( auto &span : spans ) {
			write_attrib( out, span, v, stride, offset );
			offset += span.comps;
		}
	}

	return out;
}

}
