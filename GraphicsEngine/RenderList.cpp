#include "RenderList.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

RenderList LIB_API RenderList::renderList;

bool LIB_API RenderList::add(Object*  obj, glm::mat4 mat) {
	
	if (obj->getType() == ObjectType::Light) {
		_map.insert(_map.begin(), { (Node*)obj, mat });
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

void RenderList::setSKyboxMatrix(glm::mat4 m)
{
	_skybox->setProj(m);
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
	
	glm::mat4 ef = current->_matrix;
	//glm::mat4 ef = glm::mat4(1.0);
	ef[3] = glm::vec4(0, 0, 0, 1);

	//ef = glm::translate(glm::mat4(1.0f),glm::vec3(ef[3]));
	ef = glm::scale(ef, glm::vec3(500.0f, 500.0f, 500.0f));
	
	_skybox->render(ef, _skybox->_proj);

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






