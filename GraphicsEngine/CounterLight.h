#pragma once
#include "Light.h"
#include "OmniLight.h"
#include <vector>
#include <map>


class LIB_API CounterLight {

public:
	CounterLight(LightType lightType) : _lightType{ lightType } {};
	
	void add(Light* light);
	void render();
	void clear();

	static CounterLight omniLight;
	static CounterLight spotLight;

private:
	int getFreeLightValue();
	void freeValue(int valueToFree);

	void omniSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient,
		std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular);
	void spotSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient,
		std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular);

	std::map<int, bool> valueUsed{};
	bool isCounterInitialize = false;
	std::vector<Light*> _listLight;

	LightType _lightType;

};
