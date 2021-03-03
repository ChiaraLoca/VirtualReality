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

public:
    Mesh(std::string meshName, glm::mat4 matrix, std::vector<Face> meshFaces, std::shared_ptr<Material> material);
    virtual void render();
    void set_material(std::shared_ptr<Material> material);
};
