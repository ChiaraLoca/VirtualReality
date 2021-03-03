#pragma once
#include "Camera.h"

class LIB_API OrthoCamera : public Camera
{
	int _fps=0;

public:
	OrthoCamera(std::string name, glm::mat4 matrix);
	void render();
	void setWidthHeight(int width, int height);
	void setFps(int fps);
};

