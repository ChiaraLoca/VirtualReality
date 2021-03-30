#include <GL/glew.h>
// FreeGLUT:
#include <GL/freeglut.h>

#include "Mesh.h"
#include <iostream>



Mesh::Mesh(std::string meshName, glm::mat4 matrix, std::vector<float> vertexArray, std::vector<float> normalArray,
	std::vector<float> textureArray, std::shared_ptr<Material> material)
	:Node{ meshName,matrix,ObjectType::Mesh }, _material{ material }
{
	// Generate a vertex array object and bind it:
	glGenVertexArrays(1, &_vao);						
	glBindVertexArray(_vao);

	// Generate a vertex buffer and bind it:
	glGenBuffers(1, &_vertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
	// Copy the face index data from system to video memory
	_vertexNumber = vertexArray.size();							
	glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(float),vertexArray.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


	glGenBuffers(1, &_normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _normalVbo);
	// Copy the face index data from system to video memory
	glBufferData(GL_ARRAY_BUFFER, normalArray.size() * sizeof(float), normalArray.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


	glGenBuffers(1, &_textureVbo);
	glBindBuffer(GL_ARRAY_BUFFER, _textureVbo);
	// Copy the face index data from system to video memory
	glBufferData(GL_ARRAY_BUFFER, textureArray.size() * sizeof(float), textureArray.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

}

void LIB_API Mesh::render()
{
	if (_material!= nullptr) {
		_material->render();
	}

	Node::render();

	glBindVertexArray(_vao);

	glDrawArrays(GL_TRIANGLES,0,_vertexNumber);

	// Disable VAO when not needed:
	glBindVertexArray(0);	// TODO: CHECK VAO
}

void LIB_API Mesh::set_material(std::shared_ptr<Material> material) {
	_material = material;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &_vertexVbo);
	glDeleteBuffers(1, &_normalVbo);
	glDeleteBuffers(1, &_textureVbo);
	// Dispose VAO:
	glDeleteVertexArrays(1, &_vao); // TODO: CHECK VAO
}





