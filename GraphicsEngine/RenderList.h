#pragma once
#include "Object.h"
#include "Node.h"
#include "ListCamera.h"
#include "CounterLight.h"
#include "Skybox.h"


#include <map>
#include "OrthoCamera.h"
class LIB_API RenderList : Object
{
private:
	std::map<Node*, glm::mat4> _map; // contains a reference to a specific element of the scene and its matrix multiplied for the hierarchy
	ListCamera _listCamera;
	OrthoCamera* _ortho;
	bool _showOrthoCamera = true;
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
	void setOrthoCamera(OrthoCamera* o);
	void setSkybox(Skybox* skybox);
	void setShowOrthoCamera(bool _showOrthoCamera);
	
	static RenderList renderList; // contains all the elements of the scene
};

