#include "CounterLight.h"
#include "Program.h"


#include "GL/freeglut.h"

/*Static variable*/
CounterLight LIB_API CounterLight::omniLight{LightType::OMNI};
CounterLight LIB_API CounterLight::spotLight{ LightType::SPOT };




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
#include "SpotLight.h"


void CounterLight::add(Light* light)
{
	if (_listLight.size() >= Program::maxLight)
		return;
	if (OmniLight* omni = dynamic_cast<OmniLight*>(light))
		_listLight.push_back(omni);
	if (SpotLight* spot = dynamic_cast<SpotLight*>(light))
		_listLight.push_back(spot);
}

void CounterLight::omniSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient, 
	std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular) {

	auto ambPos = Program::program.getParamLocation("lightAmbientOmni");
	Program::program.setVec3Array(ambPos, ambient.data(), sizeof(ambient.data()));

	auto diffPos = Program::program.getParamLocation("lightDiffuseOmni");
	Program::program.setVec3Array(diffPos, diffuse.data(), sizeof(diffuse.data()));

	auto specPos = Program::program.getParamLocation("lightSpecularOmni");
	Program::program.setVec3Array(specPos, specular.data(), sizeof(specular.data()));

	auto lightPos = Program::program.getParamLocation("lightPosOmni");
	Program::program.setVec3Array(lightPos, position.data(), sizeof(position.data()));
}

void CounterLight::spotSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient,
	std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular) {

	std::vector<float> cutoff(Program::maxLight - _listLight.size(), 0.0f);
	std::vector<glm::vec3> direction(Program::maxLight - _listLight.size(), glm::vec3(0.0));


	for (auto l : _listLight) {
		if (SpotLight* spot = dynamic_cast<SpotLight*>(l)) {
			cutoff.push_back(glm::radians(spot->getCutoff()));
			direction.push_back(spot->getDirection());
		}
	}

	auto ambPos = Program::program.getParamLocation("lightAmbientSpot");
	Program::program.setVec3Array(ambPos, ambient.data(), sizeof(ambient.data()));

	auto diffPos = Program::program.getParamLocation("lightDiffuseSpot");
	Program::program.setVec3Array(diffPos, diffuse.data(), sizeof(diffuse.data()));

	auto specPos = Program::program.getParamLocation("lightSpecularSpot");
	Program::program.setVec3Array(specPos, specular.data(), sizeof(specular.data()));

	auto lightPos = Program::program.getParamLocation("lightPosSpot");
	Program::program.setVec3Array(lightPos, position.data(), sizeof(position.data()));

	auto cutPos = Program::program.getParamLocation("lightCutoffSpot");
	Program::program.setFloatArray(cutPos, cutoff.data(), sizeof(cutoff.data()));

	auto dirPos = Program::program.getParamLocation("lightDirectionSpot");
	Program::program.setVec3Array(dirPos, direction.data(), sizeof(direction.data()));
}

void CounterLight::render()
{
	std::vector<glm::vec3> position(Program::maxLight - _listLight.size(), glm::vec3(0.0));
	std::vector<glm::vec3> ambient(Program::maxLight - _listLight.size(), glm::vec3(0.0));
	std::vector<glm::vec3> diffuse(Program::maxLight - _listLight.size(), glm::vec3(0.0));
	std::vector<glm::vec3> specular(Program::maxLight - _listLight.size(), glm::vec3(0.0));


	for (auto l : _listLight) {
		position.push_back(glm::vec3(l->getFinalMatrix()[3][0], l->getFinalMatrix()[3][1], l->getFinalMatrix()[3][2]));
		ambient.push_back(l->getAmbient());
		diffuse.push_back(l->getDiffuse());
		specular.push_back(l->getSpecular());
	}


	switch (_lightType)
	{
	case LightType::OMNI:
		omniSetProgramValue(position, ambient, diffuse, specular);
		break;
	case LightType::SPOT:
		spotSetProgramValue(position, ambient, diffuse, specular);
		break;
	}

}

void CounterLight::clear() {
	_listLight.clear();
}