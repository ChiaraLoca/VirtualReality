#pragma once
#include "FBO.h"
#include "Texture.h"
class LIB_API FboContainer
{
public:

	void disable();
	 FboContainer();
	 void render();
	 FBO* get(int i);
	 unsigned int getFboTexId(int i);
private:

	glm::mat4 _fboPerspective;
	glm::mat4 _ortho;
	unsigned int _vao;
	unsigned int boxVertexVbo = 0;
	unsigned int boxTexCoordVbo = 0;

	enum Eye
	{
		EYE_LEFT = 0,
		EYE_RIGHT = 1,

		// Terminator:
		EYE_LAST,
	};

	//static FBO* fboEye[2];

	FBO* fbo[EYE_LAST] = { nullptr, nullptr };
	unsigned int fboTexId[EYE_LAST] = { 0, 0 };
	int counter = 0;



	void createBox();

	void createTexBox();
	
	


};

