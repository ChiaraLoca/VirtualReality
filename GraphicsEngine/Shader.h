#pragma once



 //////////////
 // #INCLUDE //
 //////////////
#include "UtilRender.h"
	// GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C/C++:
#include <iostream>



//////////////////
// CLASS Shader //
//////////////////

/**
 * @brief OGL Shader. Management and rendering of shaders.
 */
class Shader  : public UtilRender
{
	//////////
public: //
//////////

	// Const/dest:	 
	Shader();
	~Shader();

	// Accessing data:
	bool loadFromMemory(int kind, const char* data);
	bool loadFromFile(int kind, const char* filename);


	int type;

	// Constants:
protected:
	static const unsigned int MAX_LOGSIZE = 4096;  ///< Max output size in char for a shader log

private:
	int virtual getKind(int type);
};
