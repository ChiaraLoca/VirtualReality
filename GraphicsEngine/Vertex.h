#pragma once
#include "Util.h"
class Vertex
{
public:
	glm::vec3 _vertex;
	glm::vec4 _normal;
	glm::vec2 _texture;

	Vertex(glm::vec3 _vertex, glm::vec4 _normal, glm::vec2 _texture);
	Vertex();
};

