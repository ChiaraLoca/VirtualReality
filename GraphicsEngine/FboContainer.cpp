#include "FboContainer.h"
#include "GL/glew.h"
#include "Util.h"
#include "Program.h"

// Window size:
#define APP_WINDOWSIZEX   1024                  //TODO: da passare a costruttore
#define APP_WINDOWSIZEY   512
#define APP_FBOSIZEX      APP_WINDOWSIZEX / 2
#define APP_FBOSIZEY      APP_WINDOWSIZEY / 1

void FboContainer::disable()
{
    FBO::disable();
}

FboContainer::FboContainer(int fboSizeX, int fboSizeY)
{
    
    _fboPerspective = glm::perspective(glm::radians(45.0f), (float)APP_FBOSIZEX / (float)APP_FBOSIZEY, 1.0f, 1024.0f);
    _ortho = glm::ortho(0.0f, (float)APP_WINDOWSIZEX, 0.0f, (float)APP_WINDOWSIZEY, -1.0f, 1.0f);

    createBox();
    //createTexBox();

    

    for (int c = 0; c < EYE_LAST; c++)
    {
        glGenTextures(1, &fboTexId[c]);
        glBindTexture(GL_TEXTURE_2D, fboTexId[c]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, fboSizeX, fboSizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        fbo[c] = new FBO();
        fbo[c]->bindTexture(0, FBO::BIND_COLORTEXTURE, fboTexId[c]);
        fbo[c]->bindRenderBuffer(1, FBO::BIND_DEPTHBUFFER, fboSizeX, fboSizeY);
        if (!fbo[c]->isOk())
            std::cout << "[ERROR] Invalid FBO" << std::endl;
    }
    FBO::disable();
}

void FboContainer::render()
{
    glBindVertexArray(_vao);

    // Set a matrix for the left "eye":    
    glm::mat4 f = glm::mat4(1.0f);

    // Setup the passthrough shader:
    Program::programPT.render();
    Program::programPT.setMatrix(Program::programPT.projLoc , _ortho);
    Program::programPT.setMatrix(Program::programPT.mvLoc, f);
    Program::programPT.setVec4(Program::programPT.ptColorLoc, glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

    glBindBuffer(GL_ARRAY_BUFFER, boxVertexVbo);
    glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glDisableVertexAttribArray(1); // We don't need normals for the 2D quad

    glBindBuffer(GL_ARRAY_BUFFER, boxTexCoordVbo);
    glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    // Bind the FBO buffer as texture and render:
    glBindTexture(GL_TEXTURE_2D, fboTexId[EYE_LEFT]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Do the same for the right "eye": 
    f = glm::translate(glm::mat4(1.0f), glm::vec3(APP_WINDOWSIZEX / 2, 0.0f, 0.0f));
    Program::programPT.setMatrix(Program::programPT.mvLoc, f);
    Program::programPT.setVec4(Program::programPT.ptColorLoc, glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
    glBindTexture(GL_TEXTURE_2D, fboTexId[EYE_RIGHT]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

FBO* FboContainer::get(int i)
{
    //TODO controllo sulla i
    return fbo[i];
}

void FboContainer::createBox()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Create a 2D box for screen rendering:
    glm::vec2* boxPlane = new glm::vec2[4];
    boxPlane[0] = glm::vec2(0.0f, 0.0f);
    boxPlane[1] = glm::vec2(APP_WINDOWSIZEX / 2.0f, 0.0f);
    boxPlane[2] = glm::vec2(0.0f, APP_WINDOWSIZEY);
    boxPlane[3] = glm::vec2(APP_WINDOWSIZEX / 2.0f, APP_WINDOWSIZEY);

    // Copy data into VBOs:
    glGenBuffers(1, &boxVertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, boxVertexVbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), boxPlane, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    delete[] boxPlane;

    glm::vec2* texCoord = new glm::vec2[4];
    texCoord[0] = glm::vec2(0.0f, 0.0f);
    texCoord[1] = glm::vec2(1.0f, 0.0f);
    texCoord[2] = glm::vec2(0.0f, 1.0f);
    texCoord[3] = glm::vec2(1.0f, 1.0f);
    glGenBuffers(1, &boxTexCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, boxTexCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), texCoord, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);
    delete[] texCoord;

    // OpenGL settings:     
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void FboContainer::createTexBox()
{
    
}

unsigned int FboContainer::getFboTexId(int i)
{
    return fboTexId[i];
}
