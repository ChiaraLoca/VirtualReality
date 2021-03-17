#include <GL/glew.h>
// FreeGLUT:
#include <GL/freeglut.h>

#include "Mesh.h"
#include <iostream>

/*Mesh::Mesh(std::string meshName, glm::mat4 matrix, std::vector<Face> meshFaces, std::shared_ptr<Material> material)
	:Node {meshName,matrix,ObjectType::Mesh} , _meshFaces{meshFaces}, _material{material}
{
	// Generate a vertex buffer and bind it:
	glGenBuffers(1, &_vertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);

	// Create the ptr 
	auto vertex = new float[_meshFaces.size() * 3];
	
	// Copy the face index data from system to video memory
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _meshFaces.size() * 3, vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &_normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _normalVbo); 

	glGenBuffers(1, &_textureVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _textureVbo);
}*/

Mesh::Mesh(std::string meshName, glm::mat4 matrix, std::vector<float> vertexArray, std::vector<float> normalArray,
	std::vector<float> textureArray, std::shared_ptr<Material> material)
	:Node{ meshName,matrix,ObjectType::Mesh }, _material{ material }
{
	// Generate a vertex buffer and bind it:
	glGenBuffers(1, &_vertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	// Copy the face index data from system to video memory
	_vertexNumber = vertexArray.size();							//todo: size() * sizeof(float) --> check stessa dimensione vertex=normal=texture
	glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(float),vertexArray.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _normalVbo);
	// Copy the face index data from system to video memory
	glBufferData(GL_ARRAY_BUFFER, normalArray.size() * sizeof(float), normalArray.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &_textureVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _textureVbo);
	// Copy the face index data from system to video memory
	glBufferData(GL_ARRAY_BUFFER, textureArray.size() * sizeof(float), textureArray.data(), GL_STATIC_DRAW);
}

void LIB_API Mesh::render()
{
	if (_material!= nullptr) {
		_material->render();
	}

	Node::render();

	/*for (auto const face : _meshFaces)
	{
		glBegin(GL_TRIANGLES);
			// vertex v1
			glNormal3f(face._v1._normal.x, face._v1._normal.y, face._v1._normal.z);
			glTexCoord2f(face._v1._texture.s, face._v1._texture.t);
			glVertex3f(face._v1._vertex.x, face._v1._vertex.y, face._v1._vertex.z);

			// vertex v2
			glNormal3f(face._v2._normal.x, face._v2._normal.y, face._v2._normal.z);
			glTexCoord2f(face._v2._texture.s, face._v2._texture.t);
			glVertex3f(face._v2._vertex.x, face._v2._vertex.y, face._v2._vertex.z);

			// vertex v3
			glNormal3f(face._v3._normal.x, face._v3._normal.y, face._v3._normal.z);
			glTexCoord2f(face._v3._texture.s, face._v3._texture.t);
			glVertex3f(face._v3._vertex.x, face._v3._vertex.y, face._v3._vertex.z);
		glEnd();

		glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	}*/

	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, _normalVbo);
	glNormalPointer(GL_FLOAT, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, _textureVbo);
	glTexCoordPointer(2,GL_FLOAT, 0, nullptr);

	glDrawArrays(GL_TRIANGLES,0,_vertexNumber);

}

void LIB_API Mesh::set_material(std::shared_ptr<Material> material) {
	_material = material;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &_vertexVbo);
	glDeleteBuffers(1, &_normalVbo);
	glDeleteBuffers(1, &_textureVbo);
}





