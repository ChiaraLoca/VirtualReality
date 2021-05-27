/*****************************************************************//**
 * \file   Mesh.h
 * \brief  Manages the VAO and the VBOs related to the mesh
 * 
 * \author Gruppo 1
 * \date   May 2021
 *********************************************************************/
#pragma once
#include "Node.h"
#include "Util.h"
#include "Material.h"
#include "Face.h"

class LIB_API Mesh : public Node
{
private:
    
    std::shared_ptr<Material> _material;

    unsigned int _vao;

    unsigned int _vertexVbo;
    unsigned int _normalVbo;
    unsigned int _textureVbo;

    unsigned int _vertexNumber;
    float _boundingSphereRadius;
    
public:

    Mesh(std::string meshName, glm::mat4 matrix, std::vector<float> vertexArray, std::vector<float> normalArray,
        std::vector<float> textureArray, std::shared_ptr<Material> material, float boundingSphereRadius);

    float getBoundingSphereRadius() const;
    void  setBoundingSphereRadius(float boundingSphereRadius);

    virtual void render();
    void set_material(std::shared_ptr<Material> material);
    ~Mesh();
};
