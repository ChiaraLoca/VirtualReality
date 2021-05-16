#include "RenderList.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

RenderList LIB_API RenderList::renderList;

bool LIB_API RenderList::add(Object*  obj, glm::mat4 mat) {
	
	if (obj->getType() == ObjectType::Light) {
		_map.insert(_map.begin(),{ (Node*)obj, mat });
		Light* light = (Light*)obj;
		switch (light->getLightType())
		{
		case LightType::OMNI:
			CounterLight::omniLight.add((Light*)obj);
			break;
		case LightType::SPOT:
			CounterLight::spotLight.add((Light*)obj);
			break;
		}
		
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
	CounterLight::omniLight.clear();
	CounterLight::spotLight.clear();
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

	CounterLight::omniLight.render();
	CounterLight::spotLight.render();


	for (auto i = _map.begin(); i != _map.end(); i++) {
		i->first->render();
	}



	if (_showOrthoCamera)
		_ortho->render();
}

void RenderList::setAllMatrix(Node* node) {
	if (node->getParent() != nullptr) {
		RenderList::renderList.add(node, _map.at(node->getParent()) * node->getMatrix());
	}
	else {
		RenderList::renderList.add(node, node->getMatrix());
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






