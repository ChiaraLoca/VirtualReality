#pragma once
#include "Object.h"
#include "Util.h"
#include "Texture.h"


class LIB_API Material : public Object
{
	float _shininess;
	glm::vec4 _ambient;
	glm::vec4 _diffuse;
	glm::vec4 _specular;
	glm::vec4 _emission;

	std::shared_ptr<Texture> _texture;
public:

	Material(std::string name,glm::vec4 emission, glm::vec4 ambient, glm::vec4 diffuse, 
		glm::vec4 specular, float shininess, std::shared_ptr<Texture> texture);
	
	virtual void render();
	void setTexture(std::shared_ptr<Texture> texture);
};

