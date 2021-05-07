
#include "OVRManager.h"

OVRManager  OVRManager::ovrManager;

int OVRManager::init()
{
	_ovr = new OpenVR();
	if (_ovr->init() == false)
	{
		std::cout << "[ERROR] Unable to init OpenVR" << std::endl;
		delete _ovr;
		return -2;
	}
	return 0;
}

void OVRManager::update()
{
	_ovr->update();
}

unsigned int OVRManager::getEyeLast()
{
	return OpenVR::EYE_LAST;
}

glm::mat4 OVRManager::getProjMatrix(int c)
{
	return  _ovr->getProjMatrix((OpenVR::OvEye) c, 1.0f, 1024.0f);
}

glm::mat4 OVRManager::getEye2HeadMatrix(int c)
{
	return _ovr->getEye2HeadMatrix((OpenVR::OvEye)c);
}

glm::mat4 OVRManager::getModelviewMatrix()
{
	return _ovr->getModelviewMatrix();
}

void OVRManager::pass(int c, unsigned int fboTexId)
{
	_ovr->pass((OpenVR::OvEye)c, fboTexId);
}

void OVRManager::render()
{
	_ovr->render();
}

void OVRManager::setFboSize()
{
	_fboSizeX = _ovr->getHmdIdealHorizRes();
	_fboSizeY = _ovr->getHmdIdealVertRes();
	std::cout << "   Ideal resolution :  " << _fboSizeX << "x" << _fboSizeY << std::endl;
}

int OVRManager::getfboSizeX()
{
	return _fboSizeX;
}

int OVRManager::getfboSizeY()
{
	return _fboSizeY;
}


