

#include "PerspectiveCamera.h"
#include "Program.h"
#include <GL/freeglut.h>

/**
 * @brief costructor of the perspectivecamera
 * 
 * @param name of the camera
 * @param matrix of the camera
 * @param nearPlane
 * @param farPlane
 */
LIB_API PerspectiveCamera::PerspectiveCamera(std::string name, glm::mat4 matrix, float nearPlane, float farPlane)
	:Camera{name,matrix,ObjectType::Camera,nearPlane,farPlane}
{}

/**
 * @brief render of the camera
 * sets the related matrixes
 * 
 */
void LIB_API PerspectiveCamera::render()
{ 
	Program::programPPL.setMatrix(Program::programPPL.projLoc, _view_matrix);
	Program::programPPL.setMatrix(Program::programPPL.normLoc, glm::inverseTranspose(glm::mat3(_view_matrix)));
}

/**
 * @brief set the dimension of the window on each frame, for take into consideration the eventual resize and compute the perspective matrix
 * 
 * @param width of the window
 * @param height of the window
 */
void LIB_API PerspectiveCamera::setWidthHeight(int width, int height)
{
	_width  = width;
	_height = height;

	// Update viewport size:
	glViewport(0, 0, _width, _height);

	// Refresh projection matrices:
	_view_matrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, _nearPlane, _farPlane);
}






