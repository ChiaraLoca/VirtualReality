/*****************************************************************//**
 * \file   BaseTexture.h
 * \brief  Texture base class, defines common methods and initialize freeimage
 * 
 * 
 * \author Gruppo 1
 * \date   May 2021
 *********************************************************************/
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

