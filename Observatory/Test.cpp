/*#include "Test.h"
#include <glm/gtx/string_cast.hpp>

int Test::runTest()
{

     testObject();
     testNode();

     testLista();

     testMaterial();
     testMesh();
     testTexture();

     testLight();
     testDirectionalLight();
     testOmnilLight();
     testSpotLight();

    return 1;

}



void Test::testObject(){
    std::cout << "Test object start" << std::endl;
    Object obj1{ ObjectType::Node,"Nodo1" };
    Object obj2{ ObjectType::Node,"Nodo2" };

    assert(obj1.getId() != obj2.getId());
    std::cout << "Test object finish " << std::endl;

}
void Test::testNode(){

    std::cout << "Test object node" << std::endl;


    Node node1{ "Node1",glm::mat4(1),ObjectType::Node };
    Node node2{ "Node2",glm::mat4(1),ObjectType::Node };
    Node node3{ "Node3",glm::mat4(1),ObjectType::Node };

    assert(node1.getType() == ObjectType::Node);
    assert(node2.getType() == ObjectType::Node);

    assert(node1.getId() != node2.getId());

    node1.addChild(&node2);
    node1.addChild(&node3);

    assert(node1.getNrOfChildren() == 2);


    Node* node4 = node1.getChildrenByName("Node3");

    assert(node4->getName().compare("Node3") == 0);

    glm::mat4 mat1(1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        4, 4, 4, 4);

    glm::mat4 mat2(1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        4, 8, 12, 16);

    glm::mat4 mat3(1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        7, 7, 7, 7);

    glm::mat4 res(3140.000000, 5564.000000, 7988.000000, 10412.000000,
        3560.000000, 6296.000000, 9032.000000, 11768.000000,
        3980.000000, 7028.000000, 10076.000000, 13124.000000,
        2940.000000, 5124.000000, 7308.000000, 9492.000000);

    Node root{ "root",mat1,ObjectType::Node };
    Node parent{ "parent",mat2,ObjectType::Node };
    Node leaf{ "leaf",mat3,ObjectType::Node };

    root.addChild(&parent);
    parent.addChild(&leaf);

    setAllParentTest(&root);

    assert(leaf.computeWorldCoordinates() == res);

    std::cout << "Test node finish " << std::endl;

}

void Test::testLista()
{
    std::cout << "Test lista start" << std::endl;
    glm::mat4 mat1{};
    RenderList lista;
    Node luce1{ "Luce1",mat1, ObjectType::Light };
    Node luce2{ "Luce2",mat1, ObjectType::Light };
    Node nodo1{ "Nodo1",mat1, ObjectType::Node };



    glm::mat4 mat2(1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        4, 8, 12, 16);

    lista.add(&luce1, mat1);
    lista.add(&luce2, mat1);
    lista.add(&nodo1, mat1);

    assert(lista.removeAll());


    std::cout << "Test lista finish" << std::endl;

}

void Test::testMaterial(){
    std::cout << "Test material" << std::endl;
    std::shared_ptr<Texture> texture{};

    Material material1{ "Material1",glm::vec4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),1.0f,texture };
    Material material2{};
    Material material3{ "Material3",glm::vec4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),1.0f,texture };

    assert(material1.getType() == ObjectType::Material);
    assert(material2.getType() == ObjectType::Material);

    assert(material1.getId() != material3.getId());
    
    std::cout << "Test material finish " << std::endl;

}
void Test::testMesh()
{
    std::cout << "Test mesh" << std::endl;



    std::vector<Face> meshFaces;
    std::shared_ptr<Material> material{};



    Mesh mesh1{ "Mesh1",glm::mat4(1),meshFaces,material };
    Mesh mesh2{ "Mesh2",glm::mat4(1),meshFaces,material };
    Mesh mesh3{ "Mesh3",glm::mat4(1),meshFaces,material };



    assert(mesh1.getType() == ObjectType::Mesh);
    assert(mesh2.getType() == ObjectType::Mesh);



    assert(mesh1.getId() != mesh3.getId());

    std::cout << "Test mesh finish " << std::endl;

}
void Test::testTexture()
{
    std::cout << "Test texture" << std::endl;
    Texture texture1{ "Texture1" };
    Texture texture2{ "Texture2" };
    Texture texture3{ "Texture3" };
    assert(texture1.getType() == ObjectType::Texture);
    assert(texture2.getType() == ObjectType::Texture);
    assert(texture1.getId() != texture3.getId());
    std::cout << "Test texture finish " << std::endl;

}

void Test::testLight() {
    std::cout << "Test light" << std::endl;

    //std::string name, glm::vec4 position, glm::mat4 matrix,glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular

    Light light1{ "light1",glm::vec4(1),glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };
    Light light2{ "light2",glm::vec4(1),glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };

    assert(light1.getType() == ObjectType::Light);
    assert(light2.getType() == ObjectType::Light);

    assert(light1.getId() != light2.getId());

    std::cout << "Test light finish " << std::endl;

}
void Test::testDirectionalLight()
{
    std::cout << "Test DirectionalLight" << std::endl;


    DirectionalLight light1{ "light1",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };
    DirectionalLight light2{ "light2",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };
    DirectionalLight light3{ "light3",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };

    assert(light1.getType() == ObjectType::Light);
    assert(light2.getType() == ObjectType::Light);

    assert(light1.getId() != light3.getId());


    std::cout << "Test DirectionalLight finish " << std::endl;

}
void Test::testOmnilLight()
{
    //OmniLight::OmniLight(std::string name, glm::mat4 matrix, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
    std::cout << "Test OmnilLight" << std::endl;



    OmniLight light1{ "light1",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };
    OmniLight light2{ "light2",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };
    OmniLight light3{ "light3",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1) };



    assert(light1.getType() == ObjectType::Light);
    assert(light2.getType() == ObjectType::Light);



    assert(light1.getId() != light3.getId());




    std::cout << "Test OmnilLight finish " << std::endl;

}
void Test::testSpotLight()
{
    std::cout << "Test light" << std::endl;
    //std::string name,glm::mat4 matrix,glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,float cutoff, glm::vec3 direction)

    SpotLight light1{ "light1",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),1.0f,glm::vec3(1) };
    SpotLight light2{ "light2",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),1.0f,glm::vec3(1) };
    SpotLight light3{ "light3",glm::mat4(1),glm::vec4(1),glm::vec4(1),glm::vec4(1),1.0f,glm::vec3(1) };

    assert(light1.getType() == ObjectType::Light);
    assert(light2.getType() == ObjectType::Light);

    assert(light1.getId() != light3.getId());
    std::cout << "Test light finish " << std::endl;

}

void Test::setAllParentTest(Node* parent)
{

    for (auto x : parent->getChildren())
    {

        x->setParent(parent);
        if (x->getChildren().size() != 0)
            return setAllParentTest(x);
    }

}


*/