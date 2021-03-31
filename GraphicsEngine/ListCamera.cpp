#include "ListCamera.h"

/**
 * @brief Adds a new camera to the list
 * 
 * @param camera is the pointer at the camera added to _list
 */
void  ListCamera::add(Camera* camera)
{
	_list.push_back(camera);
}

/**
 * @brief Getter of the camera that the user is currently using
 * 
 * @return Camera* is the pointer at the camera that the user is currently using 
 */
Camera*  ListCamera::getCurrentCamera()
{
	return  _list.at(_currentCamera);
}
/**
 * @brief Setter of the position, in the ListCamera, that the user want to use
 * 
 * @param i is the position in the list
 */
void  ListCamera::setCurrentCamera(int i)
{
	_currentCamera = i;
}

/**
 * @brief Getter of the size of ListCamera
 * 
 * @return the size of _list
 */
int ListCamera::size()
{
	return _list.size();
}

/**
 * @brief Getter of a camera in a specific position
 * 
 * @param i is the position in the list of the camera we want
 * @return Camera* is the camera at the position i
 */
Camera* ListCamera::at(int i)
{
	return _list.at(i);
}
