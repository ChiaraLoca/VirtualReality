#pragma once
#include "FBO.h"
#include "Texture.h"
class LIB_API FboContainer
{
public:
	FboContainer();
	~FboContainer();

	void addTexture(int idTexture);
	void render();
	void disable();

	static FboContainer fboContainer;

private:
	// Enumerations:
	enum : unsigned int 
	{
		LEFT_EYE = 0,
		RIGHT_EYE,
		MAX_EYE,
	};

	//static FBO* fboEye[2];
	FBO* fbo = new FBO();
	int counter = 0;
};

