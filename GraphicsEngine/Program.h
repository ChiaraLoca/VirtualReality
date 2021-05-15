#pragma once
#include "Shader.h"
#include "UtilRender.h"
#include "Object.h"

class LIB_API Program : public UtilRender, public Object
{
public:
	Program();
	~Program();

	bool build(Shader* vertexShader, Shader* fragmentShader);			
	bool render(void* data = nullptr);

	int projLoc;
	int mvLoc;
	int normLoc;
	int ptColorLoc;

	static Program programPPL;
	static Program programPT;
	static Program programSB;
	static int const maxLight{ 8 };
};

