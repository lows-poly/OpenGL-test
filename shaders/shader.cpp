#include "shader.h"

std::string get_file_contents( const char *filename )
{
	std::ifstream in( filename, std::ios::binary );
	if (in) {
		std::string contents;
		in.seekg( 0, std::ios::end );
		contents.resize( in.tellg() );
		in.seekg( 0, std::ios::beg );
		in.read( &contents[0], contents.size() );
		in.close();
		return ( contents );
	}
	throw (errno);
}

Shader::Shader( const char *vertex_file, const char *fragment_file )
{
	std::string vertex_code = get_file_contents( vertex_file );
	std::string fragment_code = get_file_contents( fragment_file );

	const char *vertex_source = vertex_code.c_str();
	const char *fragment_source = fragment_code.c_str();


}
