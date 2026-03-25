#version 410 core

in vec4 vertex_colour;
uniform vec4 light_colour;

out vec4 frag_colour;

void main()
{
	frag_colour = vertex_colour * light_colour;
}
