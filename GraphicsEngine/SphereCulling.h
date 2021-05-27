#pragma once
#include "Mesh.h"
#include <stdio.h>
#include "Util.h"
class SphereCulling
{
public:
	
	


	SphereCulling(float, float, glm::vec3 normale);

	bool checkIfVisible(Mesh* mesh);

	float _radius;
	glm::vec3 _center;
};

