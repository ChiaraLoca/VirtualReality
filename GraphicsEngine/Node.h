#pragma once
#include "Object.h"
#include "Util.h"


class LIB_API Node :
    public Object
{
private:
    
    glm::mat4 _finalMatrix;
    int _nChildren; 
    std::vector<Node*> _children; 
    Node* _parent = nullptr;

    glm::mat4 _matrix;
public:
  
    Node(std::string name, glm::mat4 matrix,ObjectType type=ObjectType::Node);
    virtual void render();

    glm::mat4 getMatrix() const;
    void setMatrix(glm::mat4 matrix);

    glm::mat4 getFinalMatrix() const;
    void setFinalMatrix(glm::mat4 mat);

    Node* getParent() const;
    void setParent(Node* obj);

    int getNrOfChildren() const;
    Node* getChildrenByName(const std::string name) const;
    std::vector<Node*> getChildren() const;
    void addChild(Node* child); 

    glm::mat4 computeWorldCoordinates() const;
  
};

