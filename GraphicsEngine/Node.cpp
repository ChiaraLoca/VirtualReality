// FreeGLUT:
#include <GL/freeglut.h>

#include "Node.h"

LIB_API Node::Node(std::string name, glm::mat4 matrix, ObjectType type) : Object{ type,name }
{
    _matrix = matrix;
    _nChildren = 0;
}

void LIB_API Node::render()
{
    glLoadMatrixf(glm::value_ptr(_finalMatrix));
}

glm::mat4 LIB_API Node::getMatrix() const
{
    return _matrix;
}

glm::mat4 Node::getFinalMatrix() const
{
    return _finalMatrix;
}

void LIB_API Node::setMatrix(glm::mat4 matrix)
{
    _matrix = matrix;
}

int Node::getNrOfChildren() const
{
    return _nChildren;
}

void Node::addChild(Node* child)
{
    _children.push_back(child);
    _nChildren++;
}

Node* Node::getChildrenByName(const std::string name) const
{
    for (auto x : _children)
    {
        if (x->getName().compare(name) == 0)
            return x;
    }
    return nullptr;
}

std::vector<Node*> Node::getChildren() const
{
    return _children;
}



glm::mat4 LIB_API Node::computeWorldCoordinates() const
{
    if (getParent() != nullptr)
        return getParent()->computeWorldCoordinates() * getMatrix();
    else
        return getMatrix();    
}

Node* Node::getParent() const
{
    return _parent;
}

void Node::setParent(Node* obj) {
    _parent = obj;
}


void Node::setFinalMatrix(glm::mat4 mat)
{
    _finalMatrix = mat;
}
