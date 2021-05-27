#pragma once
#include <string>
#include "GraphicsEngine.h"
class UtilClient
{
public:

	std::string buildContext(std::string path, const char* delims);
	void infoText();

	bool getRenderType(std::string _fileName);
};

