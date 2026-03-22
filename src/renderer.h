#pragma once

#include "mesh.h"
#include "shaders/texture.h"
#include "shaders/shader.h"
#include "shaders/VAO.h"
#include "shaders/EBO.h"

void renderer_draw( Shader *shader_ptr, Mesh *mesh_ptr, Texture *texture_ptr,
                    GLenum mode );
void renderer_destroy( Shader *shader_ptr, Mesh *mesh_ptr );
