#pragma once
#include "RenderList.h"
#include "Node.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"
#include "Light.h"
#include <unordered_map>


class LIB_API OVOReader
{
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> _textures;
	std::unordered_map<std::string, std::shared_ptr<Material>> _materials;
	std::string _context;
	FILE* _dat;

public:

	OVOReader(std::string context);
	~OVOReader();

	int loadObject(char* data);
	Node* loadNode(char* data);
	Material* loadMaterial(char* data);
	Mesh* loadMesh(char* data);
	Light* loadLight(char* data);
	glm::vec4 computeAmbient(glm::vec3 color);
	glm::vec4 computeSpecular(glm::vec3 color);
	glm::vec4 computeDiffuse(glm::vec3 color);
	void recursiveLoadChild(Node* node, unsigned int children);
	std::shared_ptr<Material> getMaterialFromName(const char* name);
	std::shared_ptr<Texture> getTextureFromName(const char* name);
	Object* loadAndSelect();
	Node* load(const char* fileName);
};
