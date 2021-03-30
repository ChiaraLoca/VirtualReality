

#include "PerspectiveCamera.h"
#include "Program.h"
#include <GL/freeglut.h>
LIB_API PerspectiveCamera::PerspectiveCamera(std::string name, glm::mat4 matrix, float nearPlane, float farPlane)
	:Camera{name,matrix,ObjectType::Camera,nearPlane,farPlane}
{
}

void LIB_API PerspectiveCamera::render()
{ 
	// Set perpsective matrix:
	/*glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(_view_matrix));
	glMatrixMode(GL_MODELVIEW);*/

	
	Program::program.setMatrix(Program::program.projLoc, _view_matrix);
	Program::program.setMatrix(Program::program.normLoc, glm::inverseTranspose(glm::mat3(_view_matrix)));



}




void LIB_API PerspectiveCamera::setWidthHeight(int width, int height)
{
	_width  = width;
	_height = height;

	// Update viewport size:
	glViewport(0, 0, _width, _height);

	// Refresh projection matrices:
	_view_matrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, _nearPlane, _farPlane);
}






