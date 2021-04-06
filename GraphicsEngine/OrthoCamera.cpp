#include "OrthoCamera.h"

#include "Program.h"
#include <GL/freeglut.h>

/**
 * @brief constructor of a new OrthoCamera object
 * 
 * @param name of the orthocamera
 * @param matrix of the orthocamera
 */
OrthoCamera::OrthoCamera(std::string name, glm::mat4 matrix)
	:Camera{ name,matrix,ObjectType::Camera,0,0 }
{
}

/**
 * @brief render of the orthocamera
 * it prints text to the window
 * 
 */
void LIB_API OrthoCamera::render()
{
	// Set orthographic projection:
	/*glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(_view_matrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::mat4(1)));*/

	/*

	Program::program.setMatrix(Program::program.mvLoc, glm::mat4(1));
	Program::program.setMatrix(Program::program.normLoc, glm::mat3(1));

	Program::program.setMatrix(Program::program.projLoc, _view_matrix);
	*/

	// Disable lighting before rendering 2D text:
	//glDisable(GL_LIGHTING);

	// Write some text:
	char text[64];

	sprintf(text, "FPS: %d", _fps);

	/*glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(1.0f, 2.0f);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)text);*/

	// Reactivate lighting:
	//glEnable(GL_LIGHTING);
}

/**
 * @brief set the dimension of the window on each frame, for take into consideration the eventual resize
 * 
 * @param width of the window
 * @param height of the window
 */
void LIB_API OrthoCamera::setWidthHeight(int width, int height)
{
	_width = width;
	_height = height;

	// Update viewport size:
	glViewport(0, 0, width, height);

	_view_matrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}

/**
 * @brief fps setter
 * 
 * @param fps to set
 */
void OrthoCamera::setFps(int fps)
{
	_fps = fps;
}