#pragma once
#include "Light.h"
class LIB_API SpotLight :
    public Light
{
private:
	float _cutoff;
	glm::vec3 _direction;

public:
	SpotLight(std::string name,glm::mat4 matrix, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, 
		float cutoff, glm::vec3 direction);
	virtual void render();

	float getCutoff() const { return _cutoff; };
	glm::vec3 getDirection() const { return _direction; };

};

