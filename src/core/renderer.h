#pragma once

#include "scene/mesh.h"
#include "scene/camera.h"
#include "shader/texture.h"
#include "shader/shader.h"
#include "shader/buffers/VAO.h"
#include "shader/buffers/EBO.h"

void renderer_draw( Shader *shader_ptr, Mesh *mesh_ptr, Camera *cam_ptr,
                    GLenum mode = GL_TRIANGLES );

void renderer_destroy( Shader *shader_ptr, Mesh *mesh_ptr );
