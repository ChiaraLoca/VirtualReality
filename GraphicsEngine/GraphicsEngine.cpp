// GLEW: (! before GL)
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

#include "Material.h"
#include "GraphicsEngine.h"

void LIB_API GraphicsEngine::initialize()
{
    // Initializing the required buffers
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(_posx, _posy);
   
    // FreeGLUT can parse command-line params, in case:
    int argc = 1;
    char* argv[1] = { (char*)"Something" }; // Silly initialization
    glutInit(&argc, argv);

    // Set some optional flags:
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Create the window with a specific title:   
    _windowId = glutCreateWindow(_title);

    glClearColor(_bgcolor.r, _bgcolor.g, _bgcolor.b, _bgcolor.a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f); // for a most accurate computation of the specular highlights
    glEnable(GL_NORMALIZE);
}

void LIB_API GraphicsEngine::setBackgroundColor(float r, float g, float b, float a)
{
    _bgcolor = { r,g,b,a };
}

void LIB_API GraphicsEngine::setDimension(float dimx, float dimy)
{
    _dimx = dimx;
    _dimy = dimy;
}

void LIB_API GraphicsEngine::setPosition(float posx, float posy)
{
    _posx = posx;
    _posy = posy;
}

void LIB_API GraphicsEngine::setTitle( char* title)
{
    _title = title;
}


void LIB_API GraphicsEngine::setRoot(Node* root)
{
    _root = root;
}

void GraphicsEngine::setFrames(int frames)
{
    _frames = frames;
}

int GraphicsEngine::getFrames() const
{
    return _frames;
}

Node* GraphicsEngine::getRoot() const
{
    return _root;
}

Node* GraphicsEngine::getNodeByName(std::string name) const
{
    return RenderList::renderList.getNodeByName(name);
}

void GraphicsEngine::refresh()
{
    // Force rendering refresh:
    glutPostWindowRedisplay(_windowId);
}

// Main rendering method
void GraphicsEngine::render()
{
    RenderList::renderList.removeAll();
    RenderList::renderList.setAllMatrix(_root);
    RenderList::renderList.render();
}

void GraphicsEngine::start()
{
    // Enter the main FreeGLUT processing loop:
    glutMainLoop();
}

void GraphicsEngine::free()
{
    Texture::free();
    delete(_root);
}

void GraphicsEngine::clear()
{
    // Clear the screen:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(_bgcolor.r, _bgcolor.g, _bgcolor.b, _bgcolor.a);
}

void GraphicsEngine::swapBuffer()
{
    // Swap this context's buffer:
    _frames++;
    glutSwapBuffers();
}

void GraphicsEngine::setCamera(Camera *camera) {
    RenderList::renderList.add(camera);
    RenderList::renderList.setCurrentCamera(0);
}

void GraphicsEngine::setOrthoCamera(OrthoCamera* camera) {
    RenderList::renderList.setOrthoCamera(camera);
}

void GraphicsEngine::setCurrentCamera(int i) {
    RenderList::renderList.setCurrentCamera(i);
}

Camera* GraphicsEngine::getCurrentCamera()
{
    return RenderList::renderList.getCurrentCamera();
}

void GraphicsEngine::setOption()
{
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}
void GraphicsEngine::setShowOrthoCamera(bool showOrthoCamera)
{
    RenderList::renderList.setShowOrthoCamera(showOrthoCamera);
}
void GraphicsEngine::setDisplayCallback(void(*call1)())
{
    glutDisplayFunc(call1);
}
void GraphicsEngine::setReshapeCallback(void(*call2)(int, int))
{
    glutReshapeFunc(call2);
}
void GraphicsEngine::setKeyboardCallback(void (*call)(unsigned char, int, int))
{
    glutKeyboardFunc(call);
}

void GraphicsEngine::setTimerCallback(int time, void(*call)(int), int value) {
    glutTimerFunc(time, call, value);
}



