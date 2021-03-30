#include "Material.h"
#include "Util.h"

#include "Program.h"

// FreeGLUT:
#include <GL/freeglut.h>

void LIB_API  Material::render()
{
	/*glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(_specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(_emission));*/


	auto shiPos = Program::program.getParamLocation("matShininess");
	Program::program.setFloat(shiPos, _shininess);

	auto ambPos = Program::program.getParamLocation("matAmbient");
	Program::program.setVec3(ambPos, _ambient);

	auto ambDiff = Program::program.getParamLocation("matDiffuse");
	Program::program.setVec3(ambDiff, _diffuse);

	auto emiPos = Program::program.getParamLocation("matEmission");
	Program::program.setVec3(emiPos, _emission);

	auto specPos = Program::program.getParamLocation("matSpecular");
	Program::program.setVec3(specPos, _specular);

	/*
	if (_texture != nullptr) {
		glEnable(GL_TEXTURE_2D);
		_texture->render();
	}
	else
		glDisable(GL_TEXTURE_2D);
		*/
}

void Material::setTexture(std::shared_ptr<Texture> texture)
{
	_texture = texture;
}


LIB_API Material::Material(std::string name,
	glm::vec4 emission,glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular , float shininess, std::shared_ptr<Texture>texture)
	:Object{ ObjectType::Material,name }, _shininess{ shininess }, _texture{texture},
	_ambient{ ambient }, _diffuse{ diffuse }, _specular{ specular }, _emission{ emission }
{
}

LIB_API Material::Material()
	: Object{ ObjectType::Material,"no-name material" }, _shininess{ 0.0f },
	_ambient{ glm::vec4{1.0f} }, _diffuse{ glm::vec4{1.0f} }, _specular{ glm::vec4{1.0f} }, _emission{ glm::vec4{1.0f } }
{

}




