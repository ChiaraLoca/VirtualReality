#include "FragmentShader.h"
// Glew (include it before GL.h):
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

int FragmentShader::getKind(int type)
{
    return GL_FRAGMENT_SHADER;
}
