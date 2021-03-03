#include "DirectionalLight.h"

// FreeGLUT:
#include <GL/freeglut.h>

DirectionalLight::DirectionalLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec3 direction)
	:Light(name,{direction,0.0f},matrix, ambient, diffuse, specular)
{
	//if w=0 of position x,y,z is his direction
	glEnable(GL_LIGHT0);
}

DirectionalLight::~DirectionalLight()
{
	glDisable(GL_LIGHT0);
}

void DirectionalLight::render()
{	

	glMatrixMode(GL_MODELVIEW);
	Node::render();

	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(_position));
}
