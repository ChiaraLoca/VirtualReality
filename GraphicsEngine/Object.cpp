// FreeGLUT:
#include <GL/freeglut.h>

#include "Object.h"

int Object::_counterid = 0;

/**
 * @brief constructor of a new Object
 * 
 * @param type of the object (Node, Mesh, Camera...)
 * @param name of the object, as in the .OVO file
 */
Object::Object(ObjectType type, std::string name)
{
    _id = idGenerator();
    _type = type;
    _name = name;
}

/**
 * @brief render of the object
 * to be implemented in the children
 * 
 */
void Object::render()
{
}

/**
 * @brief generates the related id
 * 
 * @return id 
 */
int LIB_API Object::idGenerator()
{
    return ++_counterid;
}

/**
 * @brief id getter
 * 
 * @return id
 */
int  LIB_API Object::getId() const
{
    return _id;
}

/**
 * @brief type getter
 * 
 * @return type
 */
ObjectType LIB_API Object::getType() const
{
    return _type;
}

/**
 * @brief type setter
 * 
 * @param type to set
 */
void LIB_API Object::setType(const ObjectType type)
{
   _type = type;
}

/**
 * @brief name getter
 * 
 * @return name 
 */
std::string LIB_API Object::getName() const
{
    return _name;
}

/**
 * @brief name setter
 * 
 * @param name to set
 */
void LIB_API Object::setName(const std::string name)
{
   _name = name;
}