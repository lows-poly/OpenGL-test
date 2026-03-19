#pragma once

#include "shaders/shader.h"
#include "shaders/VAO.h"
#include "shaders/EBO.h"

void renderer_draw( Shader *shader_ptr, VAO *vao_ptr, EBO *ebo_ptr,
                    GLuint uniform_id, float scale, GLenum mode );

void renderer_destroy( Shader *shader_ptr, VAO *vao_ptr, VBO *vbo_ptr, EBO *ebo_ptr );
