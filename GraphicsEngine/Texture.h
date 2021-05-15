#pragma once
#include "BaseTexture.h"


class LIB_API Texture :
    public BaseTexture
{
private:


public:
    Texture(std::string name);
    ~Texture();
    void loadFromFile(std::string fileName);
    void loadDefaultTexture();
    virtual void render();
};

