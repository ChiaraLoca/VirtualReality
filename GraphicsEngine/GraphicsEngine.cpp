// GLEW: (! before GL)
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

#include "Material.h"
#include "GraphicsEngine.h"

#include"Program.h"

int LIB_API GraphicsEngine::initialize()
{
    // Initializing the required buffers
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    //Initialize OpenGL_4.4 context
    glutInitContextVersion(4, 4);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);     //or glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextFlags(GLUT_DEBUG);             

    // Create window
    glutInitWindowPosition(_posx, _posy);

    // FreeGLUT can parse command-line params, in case:
    int argc = 1;
    char* argv[1] = { (char*)"Something" }; // Silly initialization
    glutInit(&argc, argv);

    // Set some optional flags:
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Create the window with a specific title:   
    _windowId = glutCreateWindow(_title);

    //Create context OpenGL_2.1
    // Init Glew (*after* the context creation):
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        std::cout << "[ERROR] " << glewGetErrorString(error) << std::endl;
        return -1;
    }
    else
        if (GLEW_VERSION_4_4)
            std::cout << "Driver supports OpenGL 4.4\n" << std::endl;
        else
        {
            std::cout << "[ERROR] OpenGL 4.4 not supported\n" << std::endl;
            return -1;
        }

    enableDebugger();

    //glClearColor(_bgcolor.r, _bgcolor.g, _bgcolor.b, _bgcolor.a);
    glClearColor(1.0, 0.0 ,0.83 ,0.5);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f); // for a most accurate computation of the specular highlights
    glEnable(GL_NORMALIZE);

    // Tell OpenGL that you want to use vertex arrays for the given attributes:
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    //Initialize shaders
    initShaders();

    return 0;
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


// Very simple debug callback:
void __stdcall DebugCallback( GLenum source, GLenum type,  GLuint id, GLenum severity,  GLsizei length,
                                const GLchar* message, GLvoid * userParam)
{
    printf("OpenGL says: %s \n", message);
}

void GraphicsEngine::enableDebugger() {
    // Enable the debug flag during context creation:
    
    glDebugMessageCallback((GLDEBUGPROC) DebugCallback, nullptr);
    // Enable debug notifications:
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    
}

LIB_API void GraphicsEngine::initShaders()
{
    Shader* vertexShader = new Shader();
    Shader* fragmentShader= new Shader();

    vertexShader->loadFromMemory(Shader::TYPE_VERTEX, vertShader);
    fragmentShader->loadFromMemory(Shader::TYPE_FRAGMENT, fragShader);

    Program::program.build(vertexShader, fragmentShader);
    Program::program.render();
    Program::program.bind(0, "in_Position");
    Program::program.bind(1, "in_Color");

    // Get shader variable locations:
    Program::program.projLoc = Program::program.getParamLocation("projection");
    Program::program.mvLoc = Program::program.getParamLocation("modelview");
}



