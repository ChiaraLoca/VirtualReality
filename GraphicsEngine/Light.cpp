#include "Light.h"


// FreeGLUT:
#include <GL/freeglut.h>


LIB_API Light::Light(std::string name, glm::vec4 position, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
	: Node{ name,matrix,ObjectType::Light }, _position{ position },
	_ambient{ ambient }, _diffuse{ diffuse }, _specular{ specular }
{
	
}

void LIB_API Light::render()
{

}
