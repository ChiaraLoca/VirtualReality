#include "ListLight.h"
#include "Program.h"
#include "OmniLight.h"
#include "SpotLight.h"
#include "GL/freeglut.h"

// Static variable /
ListLight LIB_API ListLight::omniLight{ LightType::OMNI };
ListLight LIB_API ListLight::spotLight{ LightType::SPOT };



void ListLight::add(Light* light)
{
	if (_listLight.size() >= Program::maxLight)
		return;
	if (OmniLight* omni = dynamic_cast<OmniLight*>(light))
		_listLight.push_back(omni);
	if (SpotLight* spot = dynamic_cast<SpotLight*>(light))
		_listLight.push_back(spot);
}

void ListLight::omniSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient,
	std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular) {

	auto ambPos = Program::programPPL.getParamLocation("lightAmbientOmni");
	Program::programPPL.setVec3Array(ambPos, ambient.data(), sizeof(ambient.data()));

	auto diffPos = Program::programPPL.getParamLocation("lightDiffuseOmni");
	Program::programPPL.setVec3Array(diffPos, diffuse.data(), sizeof(diffuse.data()));

	auto specPos = Program::programPPL.getParamLocation("lightSpecularOmni");
	Program::programPPL.setVec3Array(specPos, specular.data(), sizeof(specular.data()));

	auto lightPos = Program::programPPL.getParamLocation("lightPosOmni");
	Program::programPPL.setVec3Array(lightPos, position.data(), sizeof(position.data()));
}

void ListLight::spotSetProgramValue(std::vector<glm::vec3> position, std::vector<glm::vec3> ambient,
	std::vector<glm::vec3> diffuse, std::vector<glm::vec3> specular) {

	std::vector<float> cutoff(Program::maxLight - _listLight.size(), 0.0f);
	std::vector<glm::vec3> direction(Program::maxLight - _listLight.size(), glm::vec3(0.0));


	for (auto l : _listLight) {
		if (SpotLight* spot = dynamic_cast<SpotLight*>(l)) {
			cutoff.push_back(glm::radians(spot->getCutoff()));
			direction.push_back(spot->getDirection());
		}
	}

	auto ambPos = Program::programPPL.getParamLocation("lightAmbientSpot");
	Program::programPPL.setVec3Array(ambPos, ambient.data(), sizeof(ambient.data()));

	auto diffPos = Program::programPPL.getParamLocation("lightDiffuseSpot");
	Program::programPPL.setVec3Array(diffPos, diffuse.data(), sizeof(diffuse.data()));

	auto specPos = Program::programPPL.getParamLocation("lightSpecularSpot");
	Program::programPPL.setVec3Array(specPos, specular.data(), sizeof(specular.data()));

	auto lightPos = Program::programPPL.getParamLocation("lightPosSpot");
	Program::programPPL.setVec3Array(lightPos, position.data(), sizeof(position.data()));

	auto cutPos = Program::programPPL.getParamLocation("lightCutoffSpot");
	Program::programPPL.setFloatArray(cutPos, cutoff.data(), sizeof(cutoff.data()));

	auto dirPos = Program::programPPL.getParamLocation("lightDirectionSpot");
	Program::programPPL.setVec3Array(dirPos, direction.data(), sizeof(direction.data()));
}

void ListLight::render()
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

void ListLight::clear() {
	_listLight.clear();
}