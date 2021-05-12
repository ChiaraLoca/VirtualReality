// FreeGLUT:

#include "Util.h"

#include "Node.h"
#include "Program.h"

/**
 * @brief constructor of a new Node object
 * 
 * @param name of the node, as in .OVO file
 * @param matrix of the node
 * @param type of the node (Light, Camera, Mesh...)
 */
LIB_API Node::Node(std::string name, glm::mat4 matrix, ObjectType type) : Object{ type,name }
{
    _matrix = matrix;
    _nChildren = 0;
}

/**
 * @brief render of the node
 * it sets the related matrixes
 * 
 */
void LIB_API Node::render()
{
    //glLoadMatrixf(glm::value_ptr(_finalMatrix));
    
    Program::programPPL.setMatrix(Program::programPPL.mvLoc, _finalMatrix);
    Program::programPPL.setMatrix(Program::programPPL.normLoc, glm::inverseTranspose(glm::mat3(_finalMatrix)));
    
}

/**
 * @brief matrix getter
 * 
 * @return the matrix
 */
glm::mat4 LIB_API Node::getMatrix() const
{
    return _matrix;
}

/**
 * @brief final matrix getter
 * 
 * @return the final matrix
 */
glm::mat4 Node::getFinalMatrix() const
{
    return _finalMatrix;
}

/**
 * @brief matrix setter
 * 
 * @param matrix to set
 */
void LIB_API Node::setMatrix(glm::mat4 matrix)
{
    _matrix = matrix;
}

/**
 * @brief number of children getter
 * 
 * @return number of children 
 */
int Node::getNrOfChildren() const
{
    return _nChildren;
}

/**
 * @brief add a node to the related children
 * 
 * @param child to add
 */
void Node::addChild(Node* child)
{
    _children.push_back(child);
    _nChildren++;
}

/**
 * @brief return the children by its name
 * 
 * @param name of the children
 * @return the child's node
 */
Node* Node::getChildrenByName(const std::string name) const
{
    for (auto x : _children)
    {
        if (x->getName().compare(name) == 0)
            return x;
    }
    return nullptr;
}

/**
 * @brief return the children
 * 
 * @return children
 */
std::vector<Node*> Node::getChildren() const
{
    return _children;
}

/**
 * @brief computes the position in the hierarchy 
 * 
 * @return the computed matrix
 */
glm::mat4 LIB_API Node::computeWorldCoordinates() const
{
    if (getParent() != nullptr)
        return getParent()->computeWorldCoordinates() * getMatrix();
    else
        return getMatrix();    
}

/**
 * @brief parent getter
 * 
 * @return the parent
 */
Node* Node::getParent() const
{
    return _parent;
}

/**
 * @brief parent setter
 * 
 * @param parent to set
 */
void Node::setParent(Node* obj) {
    _parent = obj;
}

/**
 * @brief final matrix setter
 * 
 * @param final matrix to set
 */
void Node::setFinalMatrix(glm::mat4 mat)
{
    _finalMatrix = mat;
}
