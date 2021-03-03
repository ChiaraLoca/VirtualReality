#include "OmniLight.h"
// FreeGLUT:
#include <GL/freeglut.h>

OmniLight::OmniLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	:Light( name, glm::vec4(0, 0, 0, 1.0f),matrix, ambient, diffuse, specular){
	glEnable(GL_LIGHT1);
}

OmniLight::~OmniLight()
{
	glDisable(GL_LIGHT1);
}

void OmniLight::render()
{
	glMatrixMode(GL_MODELVIEW);
	Node::render();

	glLightfv(GL_LIGHT1, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(GL_LIGHT1, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(GL_LIGHT1, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(_position));
	
}
