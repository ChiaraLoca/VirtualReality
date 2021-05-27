#pragma once
#include "BaseTexture.h"

class Skybox :
    public BaseTexture
{
public:
    Skybox(std::string name);
    void drawSkyboxCube();
    void render(glm::mat4 ef, glm::mat4 eperspective);
    void buildCubemap();
    glm::mat4 _proj;
    void setProj(glm::mat4 proj);
private:
    // Cube VBO:
    unsigned int _vao; 
    unsigned int _cubeVboVertices = 0;
    unsigned int _cubeVboFaces = 0;
};

