#include "Texture.h"
#include <iostream>

// FreeGLUT:
#include <GL/freeglut.h>

// Texture render
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE 

// Freeimage
#define FREEIMAGE_LIB
#include <FreeImage.h>

bool Texture::freeimageInit = false;

Texture::Texture(std::string name) : Object{ ObjectType::Texture,name }
{
	if(!freeimageInit){
		FreeImage_Initialise();
		freeimageInit = true;
	}
	glGenTextures(1, &_texId);
}


void Texture::render()
{
	glBindTexture(GL_TEXTURE_2D, _texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
}


Texture::~Texture()
{
	glDeleteTextures(1, &_texId); 
}

void Texture::loadFromFile(std::string fileName)
{
	glBindTexture(GL_TEXTURE_2D, _texId);
	FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(fileName.c_str(), 0),fileName.c_str());
	FreeImage_FlipVertical(bitmap);
	
	if (FreeImage_GetBPP(bitmap) == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap),0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));
	
	else if (FreeImage_GetBPP(bitmap) == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(bitmap));
	else {
		printf(getId()+": Invalid texture");
	}

	FreeImage_Unload(bitmap);
}

void Texture::free()
{
	FreeImage_DeInitialise();
}
