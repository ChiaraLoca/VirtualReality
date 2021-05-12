#include "Material.h"
#include "Util.h"

#include "Program.h"

// FreeGLUT:
#include <GL/freeglut.h>

/**
 * @brief render of the Material
 * it sets all Material's properties
 * 
 */
void LIB_API Material::render()
{
	/*glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(_specular));
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(_emission));*/


	auto shiPos = Program::programPPL.getParamLocation("matShininess");
	Program::programPPL.setFloat(shiPos, 1.0f); //todo cambia _shininess

	auto ambPos = Program::programPPL.getParamLocation("matAmbient");
	Program::programPPL.setVec3(ambPos, _ambient);

	auto ambDiff = Program::programPPL.getParamLocation("matDiffuse");
	Program::programPPL.setVec3(ambDiff, _diffuse);

	auto emiPos = Program::programPPL.getParamLocation("matEmission");
	Program::programPPL.setVec3(emiPos, _emission);

	auto specPos = Program::programPPL.getParamLocation("matSpecular");
	Program::programPPL.setVec3(specPos, _specular);

	_texture->render();
	/*if (_texture != nullptr) {
		//glEnable(GL_TEXTURE_2D);
		_texture->render();
	}
	/*else
		glDisable(GL_TEXTURE_2D);*/
	
}

/**
 * @brief sets Material's texture
 * 
 * @param texture
 */
void Material::setTexture(std::shared_ptr<Texture> texture)
{
	_texture = texture;
}

/**
 * @brief constructor of a new Material object
 * 
 * @param name of the material in the .OVO file
 * @param emission component
 * @param ambient component
 * @param diffuse component
 * @param specular component
 * @param shininess component
 * @param texture associeted to the material (eventually)
 */
LIB_API Material::Material(std::string name,
	glm::vec4 emission,glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular , float shininess, std::shared_ptr<Texture>texture)
	:Object{ ObjectType::Material,name }, _shininess{ shininess }, _texture{texture},
	_ambient{ ambient }, _diffuse{ diffuse }, _specular{ specular }, _emission{ emission }
{
	if (_texture == nullptr) { // if there's no texture sets default texture
		std::shared_ptr<Texture> default_texture(new Texture("default_texture-"+name));
		_texture = default_texture;
		_texture->loadDefaultTexture();
	}
}
// TODO: serve?
/**
 * @brief constructor of a new Material object
 * 
 */
LIB_API Material::Material()
	: Object{ ObjectType::Material,"no-name material" }, _shininess{ 0.0f },
	_ambient{ glm::vec4{1.0f} }, _diffuse{ glm::vec4{1.0f} }, _specular{ glm::vec4{1.0f} }, _emission{ glm::vec4{1.0f } }
{

}




