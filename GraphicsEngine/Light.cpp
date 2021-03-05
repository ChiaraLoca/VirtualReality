#include "Light.h"
#include "CounterLight.h"


// FreeGLUT:
#include <GL/freeglut.h>


LIB_API Light::Light(std::string name, glm::vec4 position, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Node{ name,matrix,ObjectType::Light }, _position{ position },
	_ambient{ ambient }, _diffuse{ diffuse }, _specular{ specular },_valueLight{CounterLight::getValue()}
{
	glEnable(_valueLight);
}

LIB_API Light::~Light()
{
	glDisable(_valueLight);
}

void LIB_API Light::render()
{
	glMatrixMode(GL_MODELVIEW);
	Node::render();

	glLightfv(_valueLight, GL_AMBIENT, glm::value_ptr(_ambient));
	glLightfv(_valueLight, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glLightfv(_valueLight, GL_SPECULAR, glm::value_ptr(_specular));
	glLightfv(_valueLight, GL_POSITION, glm::value_ptr(_position));
}
