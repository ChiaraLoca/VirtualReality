/*****************************************************************//**
 * \file   OVRManager.h
 * \brief  Wrap OpenVR functionality 
 * 
 * \author Gruppo 1
 * \date   May 2021
 *********************************************************************/
#pragma once
#include "OpenVR.h";

class OVRManager
{
	
public:
	static OVRManager ovrManager;

	int init();
	void update();
	unsigned int getEyeLast();
	glm::mat4 getProjMatrix(int c);
	glm::mat4 getEye2HeadMatrix(int c);
	glm::mat4 getModelviewMatrix();
	void pass(int c, unsigned int fboTexId);
	void render();
	void setFboSize();
	int getfboSizeX();
	int getfboSizeY();

private:
	 OpenVR* _ovr;
	 int _fboSizeX = 0;
	 int _fboSizeY = 0;
};

