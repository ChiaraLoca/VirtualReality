#pragma once
#include "Object.h"

class LIB_API BaseTexture :
    public Object
{
private:
    static bool freeimageInit;
protected:
    unsigned int _texId;
public:
    BaseTexture(ObjectType type, std::string name);
    ~BaseTexture();
    static void free();
    virtual void render();
};

