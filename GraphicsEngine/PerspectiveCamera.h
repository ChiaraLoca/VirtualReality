#pragma once
#include "Camera.h"
#include "Util.h"
class LIB_API PerspectiveCamera :
    public Camera
{
public:
    PerspectiveCamera(std::string name, glm::mat4 matrix, float nearPlane, float farPlane);
    void render();
    void setWidthHeight(int width, int height);
};

