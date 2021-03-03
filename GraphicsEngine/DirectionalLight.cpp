#include "DirectionalLight.h"
#include "CounterLight.h"

// FreeGLUT:
#include <GL/freeglut.h>

DirectionalLight::DirectionalLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec3 direction)
	:Light(name, { direction,0.0f }, matrix, ambient, diffuse, specular, CounterLight::getValue())

{
	//if w=0 of position x,y,z is his direction
	glEnable(_valueLight);
}

DirectionalLight::~DirectionalLight()
{
	glDisable(_valueLight);
}

void DirectionalLight::render()
{	

	glMatrixMode(GL_MODELVIEW);
	Node::render();

	glLightfv(_valueLight, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(_valueLight, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(_valueLight, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(_valueLight, GL_POSITION, glm::value_ptr(_position));
}
