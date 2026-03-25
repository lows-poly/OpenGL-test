#version 410 core

in vec2 vertex_tex_coord;
uniform sampler2D u_texture;
uniform vec4 u_light_colour;

out vec4 frag_colour;

void main()
{
	frag_colour = texture( u_texture, vertex_tex_coord ) * light_colour;
}
