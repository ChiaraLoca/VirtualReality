#pragma once
#include "Node.h"
#include "Util.h"
#include "Material.h"
#include "Face.h"

class LIB_API Mesh : public Node
{
private:
    std::vector<Face> _meshFaces;
    std::shared_ptr<Material> _material;
    unsigned int _vertexVbo;
    unsigned int _normalVbo;
    unsigned int _textureVbo;

    unsigned int _vertexNumber;
public:
    Mesh(std::string meshName, glm::mat4 matrix, std::vector<Face> meshFaces, std::shared_ptr<Material> material); //da togliere

    Mesh(std::string meshName, glm::mat4 matrix, std::shared_ptr<float[]> vertexArray, std::shared_ptr<float[]> normalArray, 
        std::shared_ptr<float[]> textureArray, std::shared_ptr<Material> material);


    virtual void render();
    void set_material(std::shared_ptr<Material> material);
    ~Mesh();
};
