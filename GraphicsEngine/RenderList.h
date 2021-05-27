/*****************************************************************//**
 * \file   RenderList.h
 * \brief  Manage all nodes contained in a scene
 * 
 * \author Gruppo 1
 * \date   May 2021
 *********************************************************************/
#pragma once
#include "Object.h"
#include "Node.h"
#include "ListCamera.h"
#include "ListLight.h"
#include "Skybox.h"
#include "OrthoCamera.h"
#include "SphereCulling.h"

#include <map>

class LIB_API RenderList : Object
{
private:
	std::map<Node*, glm::mat4> _map; // contains a reference to a specific element of the scene and its matrix multiplied for the hierarchy
	ListCamera _listCamera;
	Skybox* _skybox;


public:
	RenderList():Object{ObjectType::List,"lista"} {};
	bool add(Object*obj, glm::mat4 mat = glm::mat4(1));
	bool removeAll();
	void render();
	Node* getNodeByName(std::string name);
	void setAllMatrix(Node* parent);
	void setCurrentCamera(int i);
	Camera* getCurrentCamera();
	void setSkybox(Skybox* skybox);
	void setSKyboxMatrix(glm::mat4 m);

	
	static RenderList renderList; // contains all the elements of the scene
};

