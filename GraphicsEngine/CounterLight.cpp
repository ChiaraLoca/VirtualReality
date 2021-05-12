#include "CounterLight.h"
#include "Program.h"

#include "GL/freeglut.h"
#include <map>

/*Static variable*/
std::map<int, bool> valueUsed;
bool isCounterInitialize = false;

/**
 * @brief Control the map valueUsed and return the first free value that is free
 * 
 * @return the position of the first free value or 0 if all position are taken
 */
int CounterLight::getFreeLightValue()
{
	//control if the map is initialized
	if (!isCounterInitialize) {
		for (auto i = 0; i < Program::maxLight; ++i) {
			valueUsed.insert(std::pair<int, bool>(GL_LIGHT0 + i, false));
		}
		isCounterInitialize = true;
	}

	//Return the first value free
	for (auto it = valueUsed.begin(); it != valueUsed.end(); ++it) {
		if (!it->second) {
			it->second = true;
			return it->first;
		}
	}
	return 0;
}

/**
 * @brief Free a value to use in the map
 * 	This method must be called before destroing a light
 * 
 * @param valueToFree value of the light that we must free
 */
void CounterLight::freeValue(int valueToFree)
{
	try {
		valueUsed.at(valueToFree) = false;
	}
	catch (const std::out_of_range& e) {
		std::cerr << valueToFree << " is not a valide light value" << std::endl;
	}
}
/**
 * @brief Reset the map by cleaning it
 * 
 */
/*void CounterLight::clear()
{
	valueUsed.clear();
	isCounterInitialize = false;
}*/

#include "OmniLight.h"
std::vector<Light*> _listLight;

void CounterLight::add(Light* light)
{
	if (_listLight.size() >= Program::maxLight)
		return;
	if (OmniLight* omni = dynamic_cast<OmniLight*>(light))
		_listLight.push_back(omni);
}

void CounterLight::render()
{
	std::vector<glm::vec3> position(Program::maxLight - _listLight.size(),glm::vec3(0.0));
	std::vector<glm::vec3> ambient(Program::maxLight - _listLight.size(), glm::vec3(0.0));
	std::vector<glm::vec3> diffuse(Program::maxLight - _listLight.size(), glm::vec3(0.0));
	std::vector<glm::vec3> specular(Program::maxLight - _listLight.size(), glm::vec3(0.0));


	for (auto l : _listLight) {
		position.push_back(glm::vec3(l->getFinalMatrix()[3][0], l->getFinalMatrix()[3][1], l->getFinalMatrix()[3][2]));
		ambient.push_back(l->getAmbient());
		diffuse.push_back(l->getDiffuse());
		specular.push_back(l->getSpecular());
	}
	
	auto ambPos = Program::programPPL.getParamLocation("lightAmbient");
	Program::programPPL.setVec3Array(ambPos, ambient.data(), sizeof(ambient.data()));

	auto diffPos = Program::programPPL.getParamLocation("lightDiffuse");
	Program::programPPL.setVec3Array(diffPos, diffuse.data(),sizeof(diffuse.data()));

	auto specPos = Program::programPPL.getParamLocation("lightSpecular");
	Program::programPPL.setVec3Array(specPos, specular.data(), sizeof(specular.data()));

	auto lightPos = Program::programPPL.getParamLocation("lightPos");
	Program::programPPL.setVec3Array(lightPos, position.data(), sizeof(position.data()));
}

void CounterLight::clear() {
	_listLight.clear();
}