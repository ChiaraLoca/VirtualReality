

#include "Util.h"
#include <iostream>
#include <string>
#include <stdio.h>

#pragma once
class UtilRender
{
public:
	UtilRender():glId(0){};
	virtual ~UtilRender() {};

	int getParamLocation(std::string name);
	void setMatrix(int param, const glm::mat4& mat);

	void setMatrix(int param, const glm::mat3& mat);


	void setFloat(int param, float value);

	void setInt(int param, int value);

	void setVec3(int param, const glm::vec3& vect);

	void setVec4(int param, const glm::vec4& vect);

	void setVec3Array(int param, glm::vec3 vect[], int sizeVec);

	void setFloatArray(int param, float vect[], int sizeVec);


	void bind(int location, const char* attribName);

public :
	static const unsigned int MAX_LOGSIZE = 4096;
	// OGL id:
	unsigned int glId ;

	enum ///< Kind of shader
	{
		TYPE_UNDEFINED = 0,
		TYPE_VERTEX,
		TYPE_FRAGMENT,
	};

};

