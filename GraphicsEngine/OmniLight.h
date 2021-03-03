#pragma once
#include "Light.h"
class LIB_API OmniLight :
    public Light
{

public:
	OmniLight(std::string name, glm::mat4 matrix, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);
	~OmniLight();
	virtual void render();
};

