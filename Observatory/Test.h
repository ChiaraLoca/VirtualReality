#include "RenderList.h"
#include "Node.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Face.h"
#include "Material.h"
#include "SpotLight.h"
#include "OmniLight.h"
#include "DirectionalLight.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
class Test
{

public:
    void testObject();
    void testNode();

    void testLista();
   
    void testMaterial();
    void testMesh();
    void testTexture();

    void testLight();
    void testDirectionalLight();
    void testOmnilLight();
    void testSpotLight();

    void setAllParentTest(Node* parent);

    int runTest();

    
};
