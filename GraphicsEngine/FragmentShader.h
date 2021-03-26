#pragma once
#include "Shader.h"
class FragmentShader :
    public Shader
{
private:
    int getKind(int type);
};

