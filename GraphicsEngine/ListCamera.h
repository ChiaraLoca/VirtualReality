/*****************************************************************//**
 * \file   ListCamera.h
 * \brief  Manages camera rendering
 * 
 * \author Gruppo 1 
 * \date   May 2021
 *********************************************************************/
#pragma once
#include "PerspectiveCamera.h"
#include <vector>

class ListCamera
{
private:
	std::vector<Camera*> _list;
	int _currentCamera = 0;

public:
	void add(Camera* camera);
	Camera* getCurrentCamera();
	void setCurrentCamera(int i);
	int size();
	Camera* at(int i);
};
