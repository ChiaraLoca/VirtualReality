#include "SpotLight.h"
#include "CounterLight.h"

// FreeGLUT:
#include <GL/freeglut.h>

SpotLight::SpotLight(std::string name,glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, 
	float cutoff, glm::vec3 direction)
	:Light( name,{ 0,0,0,1 },matrix, ambient, diffuse, specular), _cutoff{ cutoff }, _direction{direction}
{
	_valueLight = CounterLight::getValue();
	glEnable(_valueLight);
}

SpotLight::~SpotLight()
{
	glDisable(_valueLight);
}

void SpotLight::render()
{
	
	glMatrixMode(GL_MODELVIEW);
	Node::render();
	
	glLightfv(_valueLight, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(_valueLight, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(_valueLight, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(_valueLight, GL_POSITION, glm::value_ptr(_position));
	glLightfv(_valueLight, GL_SPOT_DIRECTION, glm::value_ptr(_direction));
	glLightfv(_valueLight, GL_SPOT_CUTOFF,&_cutoff);
}
