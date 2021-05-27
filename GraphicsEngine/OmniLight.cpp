#include "OmniLight.h"
#include "ListLight.h"
// FreeGLUT:
#include <GL/freeglut.h>

/**
 * @brief constructor of a new OnliLight object
 * 
 * @param name of the omnilight, as in the .OVO file
 * @param matrix of the light
 * @param ambient component
 * @param diffuse component
 * @param specular component
 */
OmniLight::OmniLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	:Light( name, glm::vec4(0,0,0, 1.0f),matrix, ambient, diffuse, specular, LightType::OMNI)
{
}
