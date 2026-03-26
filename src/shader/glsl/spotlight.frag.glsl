#version 410 core

in vec3 vertex_normal;
in vec3 frag_pos;
in vec2 vertex_tex_coord;

uniform sampler2D u_texture;
uniform sampler2D u_texture_specular;
uniform vec4 u_light_colour;
uniform vec3 u_light_pos;
uniform vec3 u_view_pos;
uniform float u_ambient;

out vec4 frag_colour;

void main()
{
	float outer_cone = 0.87f;
	float inner_cone = 0.95f;

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
	vec3 specular = texture( u_texture_specular, vertex_tex_coord ).rgb *
	                         spec * vec3( u_light_colour );

	float angle = dot( vec3(0.0f, -1.0f, 0.0f), -light_dir );
	float intensity = clamp( (angle - outer_cone) / (inner_cone - outer_cone),
	                          0.0f, 1.0f );

	vec3 lighting = ( u_ambient + (diff * intensity) + (specular * intensity) ) *
	                  attenuation;

	frag_colour = texture( u_texture, vertex_tex_coord ) *
	              vec4( lighting * vec3( u_light_colour ), 1.0 );
}
