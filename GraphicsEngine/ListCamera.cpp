#include "ListCamera.h"

void  ListCamera::add(Camera* camera)
{
	_list.push_back(camera);
}

Camera*  ListCamera::getCurrentCamera()
{
	return  _list.at(_currentCamera);
}

void  ListCamera::setCurrentCamera(int i)
{
	_currentCamera = i;
}

int ListCamera::size()
{
	return _list.size();
}

Camera* ListCamera::at(int i)
{
	return _list.at(i);
}
