#include "SpotLight.h"
#include "CounterLight.h"

// FreeGLUT:
#include <GL/freeglut.h>

SpotLight::SpotLight(std::string name,glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, 
	float cutoff, glm::vec3 direction)
	:Light( name,{ 0,0,0,1 },matrix, ambient, diffuse, specular,  LightType::SPOT), _cutoff{ cutoff }, _direction{direction}

{
}


void SpotLight::render()
{
	
	Light::render();
	/*glLightfv(_valueLight, GL_SPOT_DIRECTION, glm::value_ptr(_direction));
	glLightfv(_valueLight, GL_SPOT_CUTOFF,&_cutoff);*/
}

float SpotLight::getCutoff() const
{
	return _cutoff; 
}

glm::vec3 SpotLight::getDirection() const
{
	return _direction;
	
}
