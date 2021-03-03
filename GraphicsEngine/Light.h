#pragma once
#include "Node.h"
#include "Util.h"


class LIB_API Light : public Node 
{
protected:
	glm::vec4 _position;
	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;

	int _valueLight;

public:
	Light(std::string name, glm::vec4 position,glm::mat4 matrix,
		glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, int valueLight=10);
	
	virtual void render();
};
