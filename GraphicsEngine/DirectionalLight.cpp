#include "DirectionalLight.h"
#include "CounterLight.h"

// FreeGLUT:
#include <GL/freeglut.h>

DirectionalLight::DirectionalLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec3 direction)
	:Light(name, { direction,0.0f }, matrix, ambient, diffuse, specular)

{
}