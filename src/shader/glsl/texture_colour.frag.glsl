#version 410 core

in vec4 vertex_colour;
in vec2 vertex_tex_coord;

uniform sampler2D u_texture;

out vec4 frag_colour;

void main()
{
	frag_colour = texture( u_texture, vertex_tex_coord ) * vertex_colour;
}
