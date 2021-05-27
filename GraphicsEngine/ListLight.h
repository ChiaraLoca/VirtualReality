/*****************************************************************//**
 * \file   ListLight.h
 * \brief  Manages lights rendering
 * 
 * \author Gruppo 1
 * \date   May 2021
 *********************************************************************/
#pragma once
#include "Light.h"
#include "OmniLight.h"
#include <vector>
#include <map>


class LIB_API ListLight {

public:
	ListLight(LightType lightType) : _lightType{ lightType } {};

	void add(Light* light);
	void render();
	void clear();

	static ListLight omniLight;
	static ListLight spotLight;

private:

	void omniSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient,
		std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular);
	void spotSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient,
		std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular);

	std::vector<Light*> _listLight;
	LightType _lightType;

};