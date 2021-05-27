#include "BaseTexture.h"
// FreeGLUT:
#include <GL/freeglut.h>
// Freeimage
#define FREEIMAGE_LIB
#include <FreeImage.h>

bool BaseTexture::freeimageInit = false;

BaseTexture::BaseTexture(ObjectType type, std::string name) : Object{ type,name }
{
	if (!freeimageInit) {
		FreeImage_Initialise();
		freeimageInit = true;
	}
	glGenTextures(1, &_texId);
}

void BaseTexture::render(){}
BaseTexture::~BaseTexture(){}

void BaseTexture::free()
{
	FreeImage_DeInitialise();
}
