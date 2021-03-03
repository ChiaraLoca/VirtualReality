#include "SpotLight.h"


// FreeGLUT:
#include <GL/freeglut.h>

SpotLight::SpotLight(std::string name,glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, 
	float cutoff, glm::vec3 direction)
	:Light( name,{ 0,0,0,1 },matrix, ambient, diffuse, specular), _cutoff{ cutoff }, _direction{direction}
{

	glEnable(GL_LIGHT2);
}

SpotLight::~SpotLight()
{
	glDisable(GL_LIGHT2);
}

void SpotLight::render()
{
	
	glMatrixMode(GL_MODELVIEW);
	Node::render();
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(GL_LIGHT2, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(GL_LIGHT2, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(GL_LIGHT2, GL_POSITION, glm::value_ptr(_position));
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, glm::value_ptr(_direction));
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF,&_cutoff);
}
