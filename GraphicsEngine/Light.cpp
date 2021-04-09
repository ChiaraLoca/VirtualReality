#include "Light.h"
#include "CounterLight.h"
#include "Program.h"
#include "glm/gtx/string_cast.hpp"

// FreeGLUT:
#include <GL/freeglut.h>
#include <iostream>

/**
 * @brief Construct a new Light object 
 * 
 * @param name of the light in the file .OVO 
 * @param position of the light
 * @param matrix of of tha light. Is in object coordinate
 * @param ambient of the light
 * @param diffuse of the light 
 * @param specular of the light 
 */
LIB_API Light::Light(std::string name, glm::vec4 position, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Node{ name,matrix,ObjectType::Light }, _position{ position },
	_ambient{ ambient }, _diffuse{ diffuse }, _specular{ specular },_valueLight{CounterLight::getFreeLightValue()}
{
	//glEnable(_valueLight);
}

/**
 * @brief Destruct an Light object
 * 
 */
LIB_API Light::~Light()
{
	//glDisable(_valueLight);
	CounterLight::freeValue(_valueLight);
}

/**
 * @brief Render of the light.
 * 	It sets all the vector that the fragment shader needs
 * 
 */
void LIB_API Light::render()
{
	//glMatrixMode(GL_MODELVIEW);
	Node::render();


	/*glLightfv(_valueLight, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(_valueLight, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(_valueLight, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(_valueLight, GL_POSITION, glm::value_ptr(_position));*/

	auto ambPos = Program::program.getParamLocation("lightAmbient");
	Program::program.setVec3(ambPos, _ambient);

	auto diffPos = Program::program.getParamLocation("lightDiffuse");
	Program::program.setVec3(diffPos, _diffuse);

	auto specPos = Program::program.getParamLocation("lightSpecular");
	Program::program.setVec3(specPos, _specular);

	auto lightPos = Program::program.getParamLocation("lightPos");
	
	_position = glm::vec4(getFinalMatrix()[3][0], getFinalMatrix()[3][1], getFinalMatrix()[3][2], getFinalMatrix()[3][3]);

	Program::program.setVec3(lightPos, _position);
}
