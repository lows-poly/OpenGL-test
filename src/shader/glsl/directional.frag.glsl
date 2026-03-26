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

vec4 direct_light( void )
{
	vec3 normal = normalize( vertex_normal );
	vec3 light_dir = normalize( vec3(0.5f, 1.0f, 0.2f) );
	vec3 view_dir = normalize( u_view_pos - frag_pos );
	vec3 reflect_dir = reflect( -light_dir, normal );

	// diffuse
	float diff = max( dot( normal, light_dir ), 0.0 );

	// specular
	float spec = pow( max( dot( view_dir, reflect_dir ), 0.0 ), 32.0 );
	vec3 specular = texture( u_texture_specular, vertex_tex_coord ).rgb *
	                         spec * vec3( u_light_colour );

	vec3 lighting = u_ambient + diff + specular;
	return texture( u_texture, vertex_tex_coord ) *
	                vec4( lighting * vec3( u_light_colour ), 1.0 );
}

float near = 0.1f;
float far = 100.0f;

float linearise_depth( float depth )
{
	return ( 2.0 * near * far ) / ( far + near - ((depth * 2.0) - 1.0) *
	       (far - near) );
}

float logistic_depth( float depth )
{
	float steepness = 0.5;
	float _offset = 2.0f;
	float z_val = linearise_depth( depth );

	return ( 1 / (1 + exp( -steepness * (z_val - _offset) ) ) );
}

void apply_fog( void )
{
	float depth = logistic_depth( gl_FragCoord.z );
	frag_colour = direct_light() * (1.0f - depth) +
	              vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}

void main()
{
	frag_colour = direct_light();
}
