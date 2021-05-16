#include "RenderList.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

RenderList LIB_API RenderList::renderList;

bool LIB_API RenderList::add(Object*  obj, glm::mat4 mat) {
	
	if (obj->getType() == ObjectType::Light) {
		_map.insert(_map.begin(),{ (Node*)obj, mat });
		CounterLight::add((Light *)obj);
	}
	else if (obj->getType() == ObjectType::Camera)
	{
		_listCamera.add((Camera*)obj);
	}
	else
	{
		_map.insert(_map.end(),{ (Node*)obj, mat });
	}

	return true;
}


bool LIB_API  RenderList::removeAll() {
	_map.clear();
	Light::resetLight();
	CounterLight::clear();
	return true;
	
}

void RenderList::setShowOrthoCamera(bool showOrthoCamera) {
	_showOrthoCamera = showOrthoCamera;
}

void RenderList::render() {

	PerspectiveCamera* current = (PerspectiveCamera * )_listCamera.getCurrentCamera();
	current->setFinalMatrix(current->getInverseMatrix());
	((Node*)current)->render();
	
	for (auto i = _map.begin(); i != _map.end(); i++) {			
		i->first->setFinalMatrix(current->getInverseMatrix() * i->second);
	}

	CounterLight::render();
	
	_skybox->render(current->_matrix,current->getInverseMatrix());
	//_skybox->render();

	for (auto i = _map.begin(); i != _map.end(); i++) {
		i->first->render();
	}



	if (_showOrthoCamera)
		_ortho->render();
}

void RenderList::setAllMatrix(Node* node ) {

	

	if (node->getParent() != nullptr) {
		RenderList::renderList.add(node, _map.at(node->getParent()) * node->_matrix);
	}
	else {
		RenderList::renderList.add(node, node->_matrix);
	}
	for (auto x : node->getChildren())
		setAllMatrix(x);
}

Node* RenderList::getNodeByName(std::string name)
{
	for (auto i = _map.begin(); i != _map.end(); i++) {
		if (i->first->getName().compare(name)==0) {
			return i->first;
		}
	}
	return nullptr;
}

void  RenderList::setCurrentCamera(int i)
{
	_listCamera.setCurrentCamera(i);
}

Camera* RenderList::getCurrentCamera()
{
	return _listCamera.getCurrentCamera();
}

void RenderList::setOrthoCamera(OrthoCamera* o)
{
	_ortho = o;
}

void RenderList::setSkybox(Skybox* skybox)
{
	_skybox = skybox;
}






