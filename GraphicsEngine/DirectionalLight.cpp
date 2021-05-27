#include "DirectionalLight.h"
#include "ListLight.h"


/**
 * @brief Construct a new Directional Light:: Directional Light object
 * 
 * @param name of the light in the file .OVO
 * @param matrix of of tha light. Is in object coordinate
 * @param ambient of the light
 * @param diffuse of the light 
 * @param specular of the light 
 * @param direction of the light 
 */
DirectionalLight::DirectionalLight(std::string name, glm::mat4 matrix,
	glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, glm::vec3 direction)
	:Light(name, { direction,0.0f }, matrix, ambient, diffuse, specular,LightType::DIR
	)

{
}