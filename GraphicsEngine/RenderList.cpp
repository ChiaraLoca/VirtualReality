#include "RenderList.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

RenderList LIB_API RenderList::renderList;

/**
 * @brief Add an object to the list.
 *			It controls if it is a Light or a camera (because are managed differently)
 * 
 * \param obj is the object to add
 * \param mat is the obj matrix
 * \return true if the insert ends correctly
 */
bool LIB_API RenderList::add(Object*  obj, glm::mat4 mat) {
	
	if (obj->getType() == ObjectType::Light) {
		_map.insert(_map.begin(), { (Node*)obj, mat });
		Light* light = (Light*)obj;
		switch (light->getLightType())
		{
		case LightType::OMNI:
			ListLight::omniLight.add((Light*)obj);
			break;
		case LightType::SPOT:
			ListLight::spotLight.add((Light*)obj);
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

/**
 * @Cleanup all list in renderlist
 * 
 * \return true if the method ends correctly
 */
bool LIB_API  RenderList::removeAll() {
	_map.clear();
	ListLight::omniLight.clear();
	ListLight::spotLight.clear();
	return true;
	
}



void RenderList::setSKyboxMatrix(glm::mat4 m)
{
	_skybox->setProj(m);
}


/**
 * @brief Render in the correct order all nodes in the list
 * 
 */
void RenderList::render() {

	PerspectiveCamera* current = (PerspectiveCamera * )_listCamera.getCurrentCamera();
	SphereCulling sphereCulling{ current->getNearPlane(),current->getFarPlane() ,glm::inverseTranspose(glm::mat3(current->getView_matrix())) * glm::vec3(1)  };
	current->setFinalMatrix(current->getInverseMatrix());
	((Node*)current)->render();
	
	for (auto i = _map.begin(); i != _map.end(); i++) {
		
		i->first->setFinalMatrix(current->getInverseMatrix() * i->second);
		
		
	}

	ListLight::omniLight.render();
	ListLight::spotLight.render();
	
	glm::mat4 mv = current->getMatrix();
	mv = glm::scale(mv, glm::vec3(500.0f, 500.0f, 500.0f));

	glm::mat4 proj = _skybox->_proj;
	proj[3] = glm::vec4(0, 0, 0, 1);
	
	_skybox->render(mv, proj);

	for (auto i = _map.begin(); i != _map.end(); i++) {
		
		if (i->first->getType() == ObjectType::Mesh) {
			if (sphereCulling.checkIfVisible((Mesh*)i->first))
				i->first->render();
		}
		else
		{
			i->first->render();
		}
		
	}

}

/**
 * @brief Recorsive method used to set all final matrix to all nodes
 * 
 * \param node that needs to calculate the final matrix
 */
void RenderList::setAllMatrix(Node* node ) {

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


void RenderList::setSkybox(Skybox* skybox)
{
	_skybox = skybox;
}






