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
	/*glBindTexture(GL_TEXTURE_2D, _texId);
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
	*/
	// Load texture:
	glBindTexture(GL_TEXTURE_2D, _texId);
	FIBITMAP* fBitmap = FreeImage_Load(FreeImage_GetFileType(fileName.c_str(), 0), fileName.c_str());
	if (fBitmap == nullptr)
		std::cout << "[ERROR] Unable to load texture" << std::endl;
	int intFormat = GL_RGBA8;
	GLenum extFormat = GL_BGR;
	if (FreeImage_GetBPP(fBitmap) == 32)
	{
		intFormat = GL_RGBA8;
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
	// Load texture:
	/*FIBITMAP* fBitmap = FreeImage_Load(FreeImage_GetFileType(texFilename, 0), texFilename);
	if (fBitmap == nullptr)
		std::cout << "[ERROR] Unable to load texture" << std::endl;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FreeImage_GetWidth(fBitmap), FreeImage_GetHeight(fBitmap), 
		0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(fBitmap));

	// Free resources:
	FreeImage_Unload(fBitmap);*/
}

void Texture::free()
{
	FreeImage_DeInitialise();
}
