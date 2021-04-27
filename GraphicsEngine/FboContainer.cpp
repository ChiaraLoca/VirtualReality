#include "FboContainer.h"
#include "GL/glew.h"

// Window size:
#define APP_WINDOWSIZEX   1024                  //TODO: da passare a costruttore
#define APP_WINDOWSIZEY   512
#define APP_FBOSIZEX      APP_WINDOWSIZEX / 2
#define APP_FBOSIZEY      APP_WINDOWSIZEY / 1

FboContainer LIB_API FboContainer::fboContainer;

FboContainer::FboContainer()
{
    /*for (int eye = 0; eye < FboContainer::MAX_EYE; eye++)
    {
        fboEye[eye] = new FBO();

        fboEye[eye]->bindTexture(0, FBO::BIND_COLORTEXTURE, eye);
        fboEye[eye]->bindRenderBuffer(1, FBO::BIND_DEPTHBUFFER, APP_FBOSIZEX, APP_FBOSIZEY);
        if (!fboEye[eye]->isOk())
            std::cout << "[ERROR] Invalid FBO" << std::endl;
    }*/
}

void FboContainer::addTexture(int idTexture) {
    fbo->bindTexture(0, FBO::BIND_COLORTEXTURE, idTexture,counter);
    fbo->bindRenderBuffer(1, FBO::BIND_DEPTHBUFFER, APP_FBOSIZEX, APP_FBOSIZEY);

    ++counter;
}

void FboContainer::render()
{
    fbo->render();
}

void FboContainer::disable()
{
    fbo->disable();
}

FboContainer::~FboContainer()
{
}
