#include "Texture.h"
#include "FboContainer.h"
#include <iostream>
// Glew (include it before GL.h):
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

// Texture render
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE 

// Freeimage
#define FREEIMAGE_LIB
#include <FreeImage.h>

Texture::Texture(std::string name) : BaseTexture{ ObjectType::Texture,name }
{}


void Texture::render()
{
	// Update texture content:
	glBindTexture(GL_TEXTURE_2D, _texId);

	// Set circular coordinates:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set min/mag filters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16); //CHANGED --> cancellami prima di consegnare
}


Texture::~Texture()
{
	glDeleteTextures(1, &_texId);
}

void Texture::loadFromFile(std::string fileName)
{
	// Load texture:
	glBindTexture(GL_TEXTURE_2D, _texId);
	FIBITMAP* fBitmap = FreeImage_Load(FreeImage_GetFileType(fileName.c_str(), 0), fileName.c_str());
	if (fBitmap == nullptr)
		std::cout << "[ERROR] Unable to load texture" << std::endl;
	int intFormat = GL_COMPRESSED_RGB;
	GLenum extFormat = GL_BGR;
	if (FreeImage_GetBPP(fBitmap) == 32)
	{
		intFormat = GL_COMPRESSED_RGBA;
		extFormat = GL_BGRA;
	}

	// Update texture content:


		// Set circular coordinates:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set min/mag filters:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);

	glTexImage2D(GL_TEXTURE_2D, 0, intFormat, FreeImage_GetWidth(fBitmap), FreeImage_GetHeight(fBitmap),
		0, extFormat, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(fBitmap));

	// Free resources:
	FreeImage_Unload(fBitmap);
}

void Texture::loadDefaultTexture()
{
	const char texFilename[] = "../OVOResources/default_texture.jpg";
	loadFromFile(texFilename);
}
