#pragma once
#include "Shader.h"
class VertexShader :
    public Shader
{
private:
    int getKind(int type);
};

