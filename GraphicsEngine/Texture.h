#pragma once
#include "Object.h"


class LIB_API Texture :
    public Object
{
private:
    unsigned int _texId;
    static bool freeimageInit;
   
public:
    Texture(std::string name);
    ~Texture();
    static void free();
    void loadFromFile(std::string fileName);
    virtual void render();
};

