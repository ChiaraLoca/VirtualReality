#include "Skybox.h"
#include "Util.h"
#include "Program.h"

// Glew (include it before GL.h):
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

// Texture render
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE 

// Freeimage
#define FREEIMAGE_LIB
#include <FreeImage.h>

GLuint _vao;
float angleX = 20.0f, angleY = 1.0f;

unsigned short cubeFaces[] =
{
   0, 1, 2,
   0, 2, 3,
   3, 2, 6,
   3, 6, 7,
   4, 0, 3,
   4, 3, 7,
   6, 5, 4,
   7, 6, 4,
   4, 5, 1,
   4, 1, 0,
   1, 5, 6,
   1, 6, 2,
};

float cubeVertices[] = // Vertex and tex. coords are the same
{
   -1.0f,  1.0f,  1.0f,
   -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
   -1.0f,  1.0f, -1.0f,
   -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
};

std::string cubemapNames[] =
{
    "../OVOResources/posx.jpg",
    "../OVOResources/negx.jpg",
    "../OVOResources/posy.jpg",
    "../OVOResources/negy.jpg",
    "../OVOResources/posz.jpg",
    "../OVOResources/negz.jpg",
};

Skybox::Skybox(std::string name) : BaseTexture{ ObjectType::Skybox,name }
{
    drawSkyboxCube();
}
void Skybox::drawSkyboxCube() {
    // Init VAO:
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Load cube data into a VBO:
    glGenBuffers(1, &_cubeVboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, _cubeVboVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); // TODO: verifica
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &_cubeVboFaces);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _cubeVboFaces);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeFaces), cubeFaces, GL_STATIC_DRAW); // TODO: verifica
}

void Skybox::render()
{
    glBindVertexArray(_vao);

    // Set a matrix to move our object:
    glm::mat4 f = glm::mat4(1.0f);
    f = glm::scale(f, glm::vec3(2.0f, 2.0f, 2.0f));
    f = glm::rotate(f, glm::radians(angleX), glm::vec3(1.0f, 0.0f, 0.0f));
    f = glm::rotate(f, glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));

    // TODO: aggiungere la skybox alla lista
    // TODO: mettere matrice giusta
    glm::mat4 perspective = glm::mat4(1.0f);
    perspective = glm::perspective(glm::radians(45.0f), (float)1024 / (float)512, 1.0f, 1024.0f);

    // Set model matrix as current OpenGL matrix: 
    Program::programSB.render();
    Program::programSB.setMatrix(Program::programSB.mvLoc, f);
    //Program::program.setMatrix(Program::program.projLoc, perspective);

    glDrawElements(GL_TRIANGLES, sizeof(cubeFaces) / sizeof(unsigned short), GL_UNSIGNED_SHORT, nullptr);

    angleX += 0.5f;
}

void Skybox::buildCubemap()
{
    // Create and bind cubemap:   
    glBindTexture(GL_TEXTURE_CUBE_MAP, _texId);

    // Set params:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Set filters:
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Load sides:
    for (int curSide = 0; curSide < 6; curSide++)
    {
        // Load texture:
        FIBITMAP* fBitmap = FreeImage_Load(FreeImage_GetFileType(cubemapNames[curSide].c_str(), 0), cubemapNames[curSide].c_str());
        if (fBitmap == nullptr)
            std::cout << "[ERROR] loading file '" << cubemapNames[curSide] << "'" << std::endl;
        int intFormat = GL_RGB;
        GLenum extFormat = GL_BGR;
        if (FreeImage_GetBPP(fBitmap) == 32)
        {
            intFormat = GL_RGBA;
            extFormat = GL_BGRA;
        }

        // Fix mirroring:
        FreeImage_FlipHorizontal(fBitmap);  // Correct mirroring from cube's inside
        FreeImage_FlipVertical(fBitmap);    // Correct JPG's upside-down

        // Send texture to OpenGL:
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + curSide, 0, intFormat, FreeImage_GetWidth(fBitmap), FreeImage_GetHeight(fBitmap), 0, extFormat, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(fBitmap));

        // Free resources:
        FreeImage_Unload(fBitmap);
    }
}
