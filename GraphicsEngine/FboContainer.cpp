#include "FboContainer.h"
#include "GL/glew.h"
#include "Util.h"
#include "Program.h"


/**
 * @brief FboContainer constructor.
 *          Initilaize the eyes cameras for the stereoscopic render
 * 
 * @param fboSizeX FBO size in x axis  
 * @param fboSizeX FBO size in y axis
 */
FboContainer::FboContainer(int fboSizeX, int fboSizeY)
    :_fboSizeX{ fboSizeX }, _fboSizeY{ fboSizeY }
{
    
    _fboPerspective = glm::perspective(glm::radians(45.0f), (float)(_fboSizeX /2) / (float)_fboSizeY, 1.0f, 1024.0f);
    _ortho = glm::ortho(0.0f, (float)_fboSizeX, 0.0f, (float)_fboSizeY, -1.0f, 1.0f);

    createBox();

    for (int c = 0; c < EYE_LAST; c++)
    {
        glGenTextures(1, &fboTexId[c]);
        glBindTexture(GL_TEXTURE_2D, fboTexId[c]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _fboSizeX, _fboSizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        fbo[c] = new FBO();
        fbo[c]->bindTexture(0, FBO::BIND_COLORTEXTURE, fboTexId[c]);
        fbo[c]->bindRenderBuffer(1, FBO::BIND_DEPTHBUFFER, _fboSizeX, _fboSizeY);
        if (!fbo[c]->isOk())
            std::cout << "[ERROR] Invalid FBO" << std::endl;
    }
    FBO::disable();
}


void FboContainer::disable()
{
    FBO::disable();
}

/**
 * @brief FBOs render.
 *          It bind the vao end the fbos for each eye
 * 
 */
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

    glBindBuffer(GL_ARRAY_BUFFER, _boxVertexVbo);
    glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glDisableVertexAttribArray(1); // We don't need normals for the 2D quad

    glBindBuffer(GL_ARRAY_BUFFER, _boxTexCoordVbo);
    glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    // Bind the FBO buffer as texture and render:
    glBindTexture(GL_TEXTURE_2D, fboTexId[EYE_LEFT]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Do the same for the right "eye": 
    f = glm::translate(glm::mat4(1.0f), glm::vec3(_fboSizeX / 2, 0.0f, 0.0f));
    Program::programPT.setMatrix(Program::programPT.mvLoc, f);
    Program::programPT.setVec4(Program::programPT.ptColorLoc, glm::vec4(0.0f, 1.0f, 1.0f, 0.0f));
    glBindTexture(GL_TEXTURE_2D, fboTexId[EYE_RIGHT]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

/**
 * @brief From an index return a specific FBO
 * 
 * \param i index of the eye
 * \return pointer to an eye FBO
 */
FBO* FboContainer::get(int i)
{
    return fbo[i];
}

/**
 * @brief Create a 2D box for screen rendering for each eye
 * 
 */
void FboContainer::createBox()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Create a 2D box for screen rendering:
    glm::vec2* boxPlane = new glm::vec2[4];
    boxPlane[0] = glm::vec2(0.0f, 0.0f);
    boxPlane[1] = glm::vec2(_fboSizeX / 2.0f, 0.0f);
    boxPlane[2] = glm::vec2(0.0f, _fboSizeY);
    boxPlane[3] = glm::vec2(_fboSizeX / 2.0f, _fboSizeY);

    // Copy data into VBOs:
    glGenBuffers(1, &_boxVertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, _boxVertexVbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), boxPlane, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    delete[] boxPlane;

    glm::vec2* texCoord = new glm::vec2[4];
    texCoord[0] = glm::vec2(0.0f, 0.0f);
    texCoord[1] = glm::vec2(1.0f, 0.0f);
    texCoord[2] = glm::vec2(0.0f, 1.0f);
    texCoord[3] = glm::vec2(1.0f, 1.0f);
    glGenBuffers(1, &_boxTexCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, _boxTexCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec2), texCoord, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);
    delete[] texCoord;

    // OpenGL settings:     
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

/**
 * @brief Returns the texture id of a specific FBO
 * 
 * \param i FBO index 
 * \return texture index
 */
unsigned int FboContainer::getFboTexId(int i)
{
    return fboTexId[i];
}
