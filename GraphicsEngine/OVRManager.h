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

private:
	 OpenVR* _ovr;

	

	
};

