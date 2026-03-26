#version 410 core

in vec3 vertex_normal;
in vec3 frag_pos;
in vec2 vertex_tex_coord;

uniform vec4 u_colour;
uniform vec4 u_light_colour;
uniform vec3 u_light_pos;
uniform vec3 u_view_pos;
uniform float u_ambient;

out vec4 frag_colour;

void main()
{
	vec3 normal = normalize( vertex_normal );
	vec3 light_dir = normalize( u_light_pos - frag_pos );
	vec3 view_dir = normalize( u_view_pos - frag_pos );
	vec3 reflect_dir = reflect( -light_dir, normal );

	// attenuation
	float dist = length( u_light_pos - frag_pos );
	float attenuation = 1.0 / ( 1.0 + 0.09 * dist + 0.032 * (dist * dist) );

	// diffuse
	float diff = max( dot( normal, light_dir ), 0.0 );

	// specular
	float spec = pow( max( dot( view_dir, reflect_dir ), 0.0 ), 32.0 );
	vec3 specular = 0.5 * spec * vec3( u_light_colour );

	vec3 lighting = ( u_ambient + diff + specular ) * attenuation;
	frag_colour = u_colour * vec4( lighting * vec3( u_light_colour ), 1.0 );
}
