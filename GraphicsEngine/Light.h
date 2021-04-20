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
		glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular);
	
	virtual void render();

	static void resetLight();

	glm::vec4 getPosition() const { return _position; };
	glm::vec4 getAmbient() const { return _ambient; };
	glm::vec4 getDiffuse() const { return _diffuse; };
	glm::vec4 getSpecular() const { return _specular; };




	virtual ~Light();
};
