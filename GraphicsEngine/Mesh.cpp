// FreeGLUT:
#include <GL/freeglut.h>

#include "Mesh.h"

Mesh::Mesh(std::string meshName, glm::mat4 matrix, std::vector<Face> meshFaces, std::shared_ptr<Material> material)
	:Node {meshName,matrix,ObjectType::Mesh} , _meshFaces{meshFaces}, _material{material}
{

}

void LIB_API Mesh::render()
{
	if (_material!= nullptr) {
		_material->render();
	}

	Node::render();

	for (auto const face : _meshFaces)
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
	}
}

void LIB_API Mesh::set_material(std::shared_ptr<Material> material) {
	_material = material;
}



