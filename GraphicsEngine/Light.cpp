#include "Light.h"
#include "ListLight.h"
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
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, LightType lightType)
	: Node{ name,matrix,ObjectType::Light }, _position{ position },
	_ambient{ ambient }, _diffuse{ diffuse }, _specular{ specular }, _lightType{ lightType }
{}

/**
 * @brief Destruct an Light object
 * 
 */
LIB_API Light::~Light(){}

/**
 * @brief Render of the light.
 * 	It sets all the vector that the fragment shader needs
 * 
 */
void LIB_API Light::render()
{
	Node::render();

}

