#pragma once
#include "Shader.h"
#include "UtilRender.h"
#include "Object.h"
class LIB_API Program : public UtilRender, public Object
{
public:
	Program();
	~Program() {
		if(glId)
			glDeleteProgram(glId);
	
	}

	bool build(Shader* vertexShader, Shader* fragmentShader);			
	bool render(void* data = nullptr);

	int projLoc;
	int mvLoc;


	static Program program;
};

