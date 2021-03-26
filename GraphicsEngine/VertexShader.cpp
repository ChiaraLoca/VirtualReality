#include "VertexShader.h"
// Glew (include it before GL.h):
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

int VertexShader::getKind(int type)
{
    return GL_VERTEX_SHADER;
}