#include "OmniLight.h"
#include "CounterLight.h"
// FreeGLUT:
#include <GL/freeglut.h>

OmniLight::OmniLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	:Light( name, glm::vec4(0, 0, 0, 1.0f),matrix, ambient, diffuse, specular)
{
}
