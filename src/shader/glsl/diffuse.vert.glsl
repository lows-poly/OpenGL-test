#version 410 core

layout ( location = 0 ) in vec3 a_position;
layout ( location = 1 ) in vec3 a_normal;
layout ( location = 2 ) in vec2 a_tex_coord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 vertex_normal;
out vec3 frag_pos;
out vec2 vertex_tex_coord;

void main()
{
	vec4 world_pos = u_model * vec4( a_position, 1.0f );
	gl_Position = u_projection * u_view * world_pos;
	frag_pos = vec3( world_pos );
	vertex_normal = mat3( transpose( inverse( u_model ) ) ) * a_normal;
	vertex_tex_coord = a_tex_coord;
}
