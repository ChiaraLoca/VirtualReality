#include "BaseTexture.h"
// FreeGLUT:
#include <GL/freeglut.h>
// Freeimage
#define FREEIMAGE_LIB
#include <FreeImage.h>

// Static variable
bool BaseTexture::freeimageInit = false;

/**
 * @brief Class constructor 
 * 
 * @param type define the object type
 * @param name define the BaseTexture name
 */
BaseTexture::BaseTexture(ObjectType type, std::string name) : Object{ type,name }
{
	if (!freeimageInit) {
		FreeImage_Initialise();
		freeimageInit = true;
	}
	glGenTextures(1, &_texId);
}

/**
 * @brief Render method (to implement in the child)
 * 
 */
void BaseTexture::render(){}

/**
 * @brief Class destructor
 * 
 */
BaseTexture::~BaseTexture(){}

/**
 * @brief FreeImage release  
 * 
 */
void BaseTexture::free()
{
	FreeImage_DeInitialise();
}
