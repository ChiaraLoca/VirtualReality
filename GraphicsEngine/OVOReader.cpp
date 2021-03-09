#include "OVOReader.h"
#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>
#include "DirectionalLight.h"
#include "OmniLight.h"
#include "SpotLight.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include "Vertex.h"
#include "Face.h"


using namespace std;

// Stripped-down redefinition of OvObject (just for the chunk IDs):
class OvObject
{
public:
	enum class Type : int  ///< Type of entities
	{
		// Foundation types:
		OBJECT = 0,
		NODE,
		OBJECT2D,
		OBJECT3D,
		LIST,

		// Derived classes:
		BUFFER,
		SHADER,
		TEXTURE,
		FILTER,
		MATERIAL,
		FBO,
		QUAD,
		BOX,
		SKYBOX,
		FONT,
		CAMERA,
		LIGHT,
		BONE,
		MESH,	   // Keep them...
		SKINNED, // ...consecutive
		INSTANCED,
		PIPELINE,
		EMITTER,

		// Animation type
		ANIM,

		// Physics related:
		PHYSICS,

		// Terminator:
		LAST,
	};
};

// Stripped-down redefinition of OvMesh (just for the subtypes):
class OvMesh
{
public:
	enum class Subtype : int ///< Kind of mesh
	{
		// Foundation types:
		DEFAULT = 0,
		NORMALMAPPED,
		TESSELLATED,

		// Terminator:
		LAST,
	};
};

// Stripped-down redefinition of OvLight (just for the subtypes):
class OvLight
{
public:
	enum class Subtype : int ///< Kind of light
	{
		// Foundation types:
		OMNI = 0,
		DIRECTIONAL,
		SPOT,

		// Terminator:
		LAST,
	};
};

int OVOReader::loadObject(char* data)
{
	unsigned int position = 0;
	// OVO revision number:
	unsigned int versionId;
	memcpy(&versionId, data + position, sizeof(unsigned int));
	position += sizeof(unsigned int);
	return versionId;
}

Node* OVOReader::loadNode(char* data)
{
	unsigned int position = 0;
	// Node name:
	char nodeName[FILENAME_MAX];
	strcpy(nodeName, data + position);
	position += (unsigned int)strlen(nodeName) + 1;

	// Node matrix:
	glm::mat4 matrix;
	memcpy(&matrix, data + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Nr. of children nodes:
	unsigned int children;
	memcpy(&children, data + position, sizeof(unsigned int));
	position += sizeof(unsigned int);

	Node* thisNode = new Node{ nodeName, matrix,ObjectType::Node};
	recursiveLoadChild(thisNode, children);
	return thisNode;
}

Material* OVOReader::loadMaterial(char* data)
{
	unsigned int position = 0;
	// Material name:
	char materialName[FILENAME_MAX];
	strcpy(materialName ,data + position);
	position += (unsigned int)strlen(materialName) + 1;

	// Material term colors, starting with emissive:
	glm::vec3 emission;
	memcpy(&emission, data + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Albedo:
	glm::vec3 albedo;
	memcpy(&albedo, data + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Roughness factor:
	float roughness;
	memcpy(&roughness, data + position, sizeof(float));
	position += sizeof(float);

	// Metalness factor: SKIPPED
	position += sizeof(float);

	// Transparency factor: SKIPPED
	position += sizeof(float);

	// Albedo texture filename, or [none] if not used:
	char textureName[FILENAME_MAX];
	strcpy(textureName,data + position);
	position += (unsigned int)strlen(textureName) + 1;

	std::shared_ptr<Texture> texture = nullptr;
	std::string name{ textureName };
	if (name != "[none]") {
		texture = getTextureFromName(textureName); //if texture already exists
		if (texture == nullptr) {
			std::string path = _context + name;
			texture = std::shared_ptr<Texture>{ new Texture{textureName} };
			texture->loadFromFile(path);
			_textures.insert(std::pair<std::string, std::shared_ptr<Texture>>(texture->getName(), texture));
		}
	}
	
	Material *newMaterial = new Material{ materialName,glm::vec4{emission, 1},computeAmbient(albedo),computeDiffuse(albedo),computeSpecular(albedo), (1 - sqrt(roughness)) * 128, texture };
	return newMaterial;
}

Mesh* OVOReader::loadMesh(char* data)
{
	unsigned int position = 0;

	// Mesh name:
	char meshName[FILENAME_MAX];
	strcpy(meshName,data + position);
	position += (unsigned int)strlen(meshName) + 1;

	// Mesh matrix:
	glm::mat4 matrix;
	memcpy(&matrix, data + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Mesh nr. of children nodes:
	unsigned int children;
	memcpy(&children, data + position, sizeof(unsigned int));
	position += sizeof(unsigned int);

	// Optional target node, or [none] if not used:
	char targetName[FILENAME_MAX];
	strcpy(targetName, data + position);
	position += (unsigned int)strlen(targetName) + 1;

	// Mesh subtype (see OvMesh SUBTYPE enum): SKIPPED
	position += sizeof(unsigned char);

	// Material name, or [none] if not used:
	char materialName[FILENAME_MAX];
	strcpy(materialName, data + position);
	position += (unsigned int)strlen(materialName) + 1;

	// Mesh bounding sphere radius: SKIPPED
	position += sizeof(float);

	// Mesh bounding box minimum corner: SKIPPED
	position += sizeof(glm::vec3);

	// Mesh bounding box maximum corner: SKIPPED
	position += sizeof(glm::vec3);

	// Optional physics properties: SKIPPED
	unsigned char hasPhysics;
	memcpy(&hasPhysics, data + position, sizeof(unsigned char));
	position += sizeof(unsigned char);

	if (hasPhysics)
	{
		/**
		  * Mesh physics properties.
		  */
		struct PhysProps
		{
			// Pay attention to 16 byte alignement (use padding):
			unsigned char type;
			unsigned char contCollisionDetection;
			unsigned char collideWithRBodies;
			unsigned char hullType;

			// Vector data:
			glm::vec3 massCenter;

			// Mesh properties:
			float mass;
			float staticFriction;
			float dynamicFriction;
			float bounciness;
			float linearDamping;
			float angularDamping;
			void* physObj;
			unsigned int nrOfHulls;
			void* hull;
			unsigned int _pad;
		};
		position += sizeof(PhysProps);
	}

	// Nr. of LODs: SKIPPED (at the moment is always 1 but it could be modify in the future)
	position += sizeof(unsigned int);

	// in case there are more than 1 LOD the following part should be added in a loop

	// Nr. of vertices:
	unsigned int vertices;
	memcpy(&vertices, data + position, sizeof(unsigned int));
	position += sizeof(unsigned int);

	// ...and faces:
	unsigned int faces;
	memcpy(&faces, data + position, sizeof(unsigned int));
	position += sizeof(unsigned int);

	std::vector<Vertex> meshVertexes;

	// Interleaved and compressed vertex/normal/UV/tangent data:
	for (unsigned int c = 0; c < vertices; c++)
	{
		// Vertex coords:
		glm::vec3 vertex;
		memcpy(&vertex, data + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);

		// Vertex normal:
		unsigned int normalData;
		memcpy(&normalData, data + position, sizeof(unsigned int));
		glm::vec4 normal = glm::unpackSnorm3x10_1x2(normalData);
		position += sizeof(unsigned int);

		// Texture coordinates:
		unsigned int textureData;
		memcpy(&textureData, data + position, sizeof(unsigned int));
		glm::vec2 uv = glm::unpackHalf2x16(textureData);
		position += sizeof(unsigned int);

		// Tangent vector: SKIPPED
		position += sizeof(unsigned int);

		Vertex meshVertex;

		meshVertex._vertex = vertex;
		meshVertex._normal = normal;
		meshVertex._texture = uv;

		meshVertexes.push_back(meshVertex);
	}

	std::vector<Face> meshFaces;
	// Creation of the array for the mesh
	std::shared_ptr<float[]> vertexArray (new float[faces * 3]);
	std::shared_ptr<float[]>  normalArray(new float[faces * 3]);
	std::shared_ptr<float[]>  textureArray(new float[faces * 2]);

	// Faces:
	/*for (unsigned int c = 0; c < faces; c++)
	{
		// Face indexes:
		unsigned int face[3];
		memcpy(face, data + position, sizeof(unsigned int) * 3);
		position += sizeof(unsigned int) * 3;

		Face meshFace(meshVertexes.at(face[0]), meshVertexes.at(face[1]), meshVertexes.at(face[2]));
		meshFaces.push_back(meshFace);

	}*/
	
	int i{ 0 };
	for (auto ver : meshVertexes) {
		vertexArray[i] = ver._vertex.x;
		vertexArray[i+1] = ver._vertex.y;
		vertexArray[i+2] = ver._vertex.z;
		i += 3;
	}

	i = 0;
	for (auto norm : meshVertexes) {
		normalArray[i] = norm._normal.x;
		normalArray[i + 1] = norm._normal.y;
		normalArray[i + 2] = norm._normal.z;
		i += 3;
	}

	i =  0;
	for (auto tex : meshVertexes) {
		vertexArray[i] = tex._texture.s;
		vertexArray[i + 1] = tex._texture.t;
		i += 2;
	}


	std::shared_ptr<Material> material = getMaterialFromName(materialName);
	Mesh* thisMesh = new Mesh{ meshName, matrix, vertexArray, normalArray, textureArray, material };

	recursiveLoadChild(thisMesh, children);
	return thisMesh;
}

Light* OVOReader::loadLight(char* data)
{
	unsigned int position = 0;
	// Light name:
	char lightName[FILENAME_MAX];
	strcpy(lightName,data + position);
	position += (unsigned int)strlen(lightName) + 1;

	// Light matrix:
	glm::mat4 matrix;
	memcpy(&matrix, data + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Nr. of children nodes:
	unsigned int children;
	memcpy(&children, data + position, sizeof(unsigned int));
	position += sizeof(unsigned int);

	// Optional target node name, or [none] if not used:
	char targetName[FILENAME_MAX];
	strcpy(targetName,data + position);
	position += (unsigned int)strlen(targetName) + 1;

	// Light subtype (see OvLight SUBTYPE enum):
	unsigned char subtype;
	memcpy(&subtype, data + position, sizeof(unsigned char));
	char subtypeName[FILENAME_MAX];
	switch ((OvLight::Subtype) subtype)
	{
	case OvLight::Subtype::DIRECTIONAL: strcpy(subtypeName,"directional"); break;
	case OvLight::Subtype::OMNI: strcpy(subtypeName,"omni"); break;
	case OvLight::Subtype::SPOT: strcpy(subtypeName,"spot"); break;
	default: strcpy(subtypeName,"UNDEFINED");
	}
	position += sizeof(unsigned char);

	// Albedo light color:
	glm::vec3 color;
	memcpy(&color, data + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Influence radius: SKIPPED
	position += sizeof(float);

	// Direction:
	glm::vec3 direction;
	memcpy(&direction, data + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Cutoff:
	float cutoff;
	memcpy(&cutoff, data + position, sizeof(float));
	position += sizeof(float);

	// Exponent: SKIPPED
	position += sizeof(float);

	// Cast shadow flag: SKIPPED
	position += sizeof(unsigned char);

	// Volumetric lighting flag: SKIPPED
	position += sizeof(unsigned char);

	Light* thisLight = nullptr;
	glm::vec4 ambient = computeAmbient(color);
	glm::vec4 specular = computeSpecular(color);
	glm::vec4 diffuse = computeDiffuse(color);

	// transform lightname to string (for constructor)
	std::string strlightName;
	strlightName.append(lightName);

	switch ((OvLight::Subtype) subtype)
	{
	case OvLight::Subtype::DIRECTIONAL: thisLight = new DirectionalLight{ strlightName,matrix,ambient,diffuse,specular,direction }; break;
	case OvLight::Subtype::OMNI: thisLight = new OmniLight{ strlightName,matrix,ambient,diffuse, specular }; break;
	case OvLight::Subtype::SPOT: thisLight = new SpotLight{ strlightName,matrix,ambient,diffuse, specular, cutoff ,direction }; break;
	}

	if (thisLight != nullptr) {
		recursiveLoadChild(thisLight, children);
	}

	return thisLight;
}

glm::vec4 OVOReader::computeAmbient(glm::vec3 color)
{
	return glm::vec4{ color * 0.2f ,1 };
}

glm::vec4 OVOReader::computeSpecular(glm::vec3 color)
{
	return glm::vec4{ color * 0.4f, 1 };
}

glm::vec4 OVOReader::computeDiffuse(glm::vec3 color)
{
	return glm::vec4{ color * 0.6f, 1 };
}

void OVOReader::recursiveLoadChild(Node* node, unsigned int children)
{
	while (node->getNrOfChildren() < children) {
		Node* child = dynamic_cast<Node*>(loadAndSelect()); // if it's not Material nor Object
		if (child != nullptr) {
			node->addChild(child);
			child->setParent(node);
		}
	}
}

std::shared_ptr<Material> OVOReader::getMaterialFromName(const char* name)
{
	if (_materials.count(name))
		return _materials.at(name);
	return nullptr;
}

std::shared_ptr<Texture> OVOReader::getTextureFromName(const char* name)
{
	if (_textures.count(name))
		return _textures.at(name);
	return nullptr;
}

Object* OVOReader::loadAndSelect()
{
	Object* result;

	// Parse chuncks:
	unsigned int chunkId, chunkSize;
	fread(&chunkId, sizeof(unsigned int), 1, _dat);
	if (feof(_dat)!=0)
		return nullptr;
	fread(&chunkSize, sizeof(unsigned int), 1, _dat);

	// Load whole chunk into memory:
	char* data = new char[chunkSize];
	if (fread(data, sizeof(char), chunkSize, _dat) != chunkSize)
	{
		fclose(_dat);
		delete[] data;
		return nullptr;
	}

	// Parse chunk information according to its type:
	switch ((OvObject::Type) chunkId)
	{
	case OvObject::Type::OBJECT:
	{
		loadObject(data);
		result = nullptr;
	}
	break;
	case OvObject::Type::MATERIAL:
	{
		Material* material = loadMaterial(data);
		_materials.insert(std::pair<std::string, Material*>(material->getName(), material));
		result = material;
	}
	break;
	case OvObject::Type::NODE:
	{
		result = loadNode(data);
	}
	break;
	case OvObject::Type::MESH:
	{
		result = loadMesh(data);
	}
	break;
	case OvObject::Type::LIGHT:
	{
		result = loadLight(data);
	}
	break;
	default:
		result = nullptr;
	}

	// Release chunk memory:
	delete[] data;
	return result;
}

Node* OVOReader::load(const char* fileName)
{
	std::string str = _context + fileName;
	// Open file:
	_dat = fopen( str.c_str(), "rb");
	if (_dat == nullptr)
	{
		cout << "ERROR: unable to open file '" << fileName << "'" << endl;
		return nullptr;
	}
	Node* root = nullptr;

	while (feof(_dat)==0) {
		Object* obj = loadAndSelect();
		if (obj != nullptr)
			root = dynamic_cast<Node*>(obj);
	}

	// Done:
	fclose(_dat);
	return root;
}

OVOReader::OVOReader(std::string context)
	:_context{context}
{
}

OVOReader::~OVOReader()
{
}




