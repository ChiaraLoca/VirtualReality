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
