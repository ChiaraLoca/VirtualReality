#include "OmniLight.h"
#include "CounterLight.h"
// FreeGLUT:
#include <GL/freeglut.h>

OmniLight::OmniLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	:Light( name, glm::vec4(0, 0, 0, 1.0f),matrix, ambient, diffuse, specular){
	glEnable(_valueLight);
}

OmniLight::~OmniLight()
{
	glDisable(_valueLight);
}

void OmniLight::render()
{
	glMatrixMode(GL_MODELVIEW);
	Node::render();

	glLightfv(_valueLight, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(_valueLight, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(_valueLight, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(_valueLight, GL_POSITION, glm::value_ptr(_position));
	
}
