#version 410 core

out vec4 frag_colour;

uniform vec4 u_light_colour;

void main()
{
	frag_colour = u_light_colour;
}
