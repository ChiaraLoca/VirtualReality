#pragma once
#include "Light.h"
#include "Util.h"
#include "Object.h"

class LIB_API DirectionalLight :
    public Light
{
public:
	DirectionalLight (std::string name, glm::mat4 matrix, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec3 direction);
	~DirectionalLight();
	virtual void render();
};

