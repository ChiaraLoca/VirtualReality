#pragma once
#include "FBO.h"
#include "Texture.h"
class LIB_API FboContainer
{
public:

	 void disable();
	 FboContainer(int fboSizeX, int fboSizeY);
	 void render();
	 FBO* get(int i);
	 unsigned int getFboTexId(int i);
private:

	glm::mat4 _fboPerspective;
	glm::mat4 _ortho;
	unsigned int _vao;
	unsigned int _boxVertexVbo = 0;
	unsigned int _boxTexCoordVbo = 0;

	int _fboSizeX;
	int _fboSizeY;

	enum Eye
	{
		EYE_LEFT = 0,
		EYE_RIGHT = 1,

		// Terminator:
		EYE_LAST,
	};

	FBO* fbo[EYE_LAST] = { nullptr, nullptr };
	unsigned int fboTexId[EYE_LAST] = { 0, 0 };
	
	void createBox();

};

