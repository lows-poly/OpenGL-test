#version 410 core

layout ( location = 0 ) in vec3 a_position;
layout ( location = 1 ) in vec4 a_colour;
layout ( location = 2 ) in vec2 a_tex_coord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 vertex_colour;
out vec2 vertex_tex_coord;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4( a_position, 1.0f );
	vertex_colour = a_colour; 
	vertex_tex_coord = a_tex_coord;
}
