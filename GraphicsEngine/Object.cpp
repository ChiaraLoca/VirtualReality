// FreeGLUT:
#include <GL/freeglut.h>

#include "Object.h"

int Object::_counterid = 0;

Object::Object(ObjectType type, std::string name)
{
    _id = idGenerator();
    _type = type;
    _name = name;
}

void Object::render()
{
}

int LIB_API Object::idGenerator()
{
    return ++_counterid;
}

int  LIB_API Object::getId() const
{
    return _id;
}

ObjectType LIB_API Object::getType() const
{
    return _type;
}

void LIB_API Object::setType(const ObjectType type)
{
   _type = type;
}

std::string LIB_API Object::getName() const
{
    return _name;
}

void LIB_API Object::setName(const std::string name)
{
   _name = name;
}