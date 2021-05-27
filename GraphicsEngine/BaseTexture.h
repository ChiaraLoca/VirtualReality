#pragma once
#include "Object.h"
//Classe base di texture,definisce metodi in comune e inizializza freeimage
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

