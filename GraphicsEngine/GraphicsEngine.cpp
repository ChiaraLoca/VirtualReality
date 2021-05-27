// GLEW: (! before GL)
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

#include "Util.h"
#include "Material.h"
#include "GraphicsEngine.h"
#include "Program.h"
#include "FboContainer.h"
#include "OVRManager.h"



/**
 * @brief Initialization of all component of the GraphicsEngine
 * 
 * @return  0   if the initialization was successful 
 *          -1  if the initialization had a problem with GLEW
 *          -2  if the initialization had a proble with GLEW version
 */
int LIB_API GraphicsEngine::initialize()
{
    // FreeGLUT can parse command-line params, in case:
    int argc = 1;
    char* argv[1] = { (char*)"Something" }; // Silly initialization
    glutInit(&argc, argv);

    // Initializing the required buffers
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //Initialize OpenGL_4.4 context
    glutInitContextVersion(4, 4);
    glutInitContextProfile(GLUT_CORE_PROFILE);     //or glutInitContextProfile(GLUT_COMPABILITY_PROFILE);
    glutInitContextFlags(GLUT_DEBUG);

    // Create window
    glutInitWindowPosition(_posx, _posy);
    glutInitWindowSize(_dimx, _dimy);



    // Set some optional flags:
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    // Create the window with a specific title:   
    _windowId = glutCreateWindow(_title);

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
            return -2;
        }

    enableDebugger();

    glClearColor(_bgcolor.r, _bgcolor.g, _bgcolor.b, _bgcolor.a);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f); // for a most accurate computation of the specular highlights



    //Initialize shaders
    initShaders();

    //Initalize FBOs
    //initFbo();
    if (_stereoscopicRender){
        if (OVRManager::ovrManager.init() < 0)
        {
            //return -3;
            _stereoscopicRender = false;
            _fboContainer = new FboContainer(_dimx, _dimy);
        }
        else {
            OVRManager::ovrManager.setFboSize();
            _fboContainer = new FboContainer(OVRManager::ovrManager.getfboSizeX(), OVRManager::ovrManager.getfboSizeY());
        }
    }
    else
    {
        _fboContainer = new FboContainer(_dimx,_dimy);
    }
    // Load cubemap:
    _skybox = new Skybox("Skybox");    
    _skybox->buildCubemap();
    RenderList::renderList.setSkybox(_skybox);

   

    glViewport(0, 0, _dimx, _dimy);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    enableWireframe(false);

    return 0;
}

/**
 * @brief Setter of the background color
 * 
 * @param r is the component red
 * @param g is the component green
 * @param b is the component blue
 * @param a is the component alpha
 */
void LIB_API GraphicsEngine::setBackgroundColor(float r, float g, float b, float a)
{
    _bgcolor = { r,g,b,a };
}

/**
 * @brief Setter of the default deminsion of the window
 * 
 * @param dimx is the dimension in the x-axis
 * @param dimy is the dimension in the y-axis
 */
void LIB_API GraphicsEngine::setDimension(float dimx, float dimy)
{
    _dimx = dimx;
    _dimy = dimy;
}

/**
 * @brief Setter of the default position of the window
 * 
 * @param posx is the position in the x-axis
 * @param posy is the position in the y-axis
 */
void LIB_API GraphicsEngine::setPosition(float posx, float posy)
{
    _posx = posx;
    _posy = posy;
}

/**
 * @brief Setter of the title of the window
 * 
 * @param title of the window
 */
void LIB_API GraphicsEngine::setTitle( char* title)
{
    _title = title;
}

/**
 * @brief Setter of the root node of the scene
 * 
 * @param root is the node form where the scene starts
 */
void LIB_API GraphicsEngine::setRoot(Node* root)
{
    _root = root;
}

/**
 * @brief Setter of the frames value
 *  Usually used to reset this value 
 * 
 * @param frames value of the frames (usually 0)
 */
void GraphicsEngine::setFrames(int frames)
{
    _frames = frames;
}

/**
 * @brief Getter of the frames value
 * 
 * @return _frames calculate by the GraphicsEngine
 */
int GraphicsEngine::getFrames() const
{
    return _frames;
}

/**
 * @brief Setter of the root node of the scene
 * 
 * @return _root  is the node form where the scene starts
 */
Node* GraphicsEngine::getRoot() const
{
    return _root;
}

/**
 * @brief From a string name (settet by the user) returns the node
 * 
 * @param name of the node that we are looking for
 * @return Node* that has the name "name"
 */
Node* GraphicsEngine::getNodeByName(std::string name) const
{
    return RenderList::renderList.getNodeByName(name);
}

/**
 * @brief Force the refresh of the scene
 * 
 */
void GraphicsEngine::refresh()
{
    // Force rendering refresh:
    glutPostWindowRedisplay(_windowId);
}
void GraphicsEngine::resize()
{
   /* fboPerspective = glm::perspective(glm::radians(45.0f), (float)APP_FBOSIZEX / (float)APP_FBOSIZEY, 1.0f, 1024.0f);
    ortho = glm::ortho(0.0f, (float)APP_WINDOWSIZEX, 0.0f, (float)APP_WINDOWSIZEY, -1.0f, 1.0f);*/

    // (bad) trick to avoid window resizing:
    
        glutReshapeWindow(_dimx, _dimy);
}



/**
 * @brief Main rendering method
 *  It calls the main method of RenderList 
 * 
 */
void GraphicsEngine::render()
{
    
    if (_stereoscopicRender) {
        stereoscopicRender(); 
    }
    else {
        
        standardRender();
    }
}

void GraphicsEngine::standardRender()
{
    RenderList::renderList.removeAll();
    RenderList::renderList.setAllMatrix(_root);
    //RenderList::renderList.setSkybox(_skybox);
    for (int c = 0; c < 2; c++) // fix hardcode
    {
        
        // Render into this FBO:
        _fboContainer->get(c)->render();

        // Clear the FBO content:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Camera* camera = (Camera*)getCurrentCamera();
        RenderList::renderList.setSKyboxMatrix(camera->_view_matrix);
        //setStandardShader();
        RenderList::renderList.render();
 
    }

    _fboContainer->disable();
    glViewport(0, 0, _dimx, _dimy);
    //setPassthroughShader();
    _fboContainer->render();

    // Clear the FBO content:
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setSkyboxShader();
    _skybox->render();
    glViewport(0, 0, _dimx, _dimy);*/
}
void GraphicsEngine::stereoscopicRender()
{
    RenderList::renderList.removeAll();

    RenderList::renderList.setAllMatrix(_root);
    //RenderList::renderList.setSkybox(_skybox);

    OVRManager::ovrManager.update();

    glm::mat4 headPos = OVRManager::ovrManager.getModelviewMatrix();

    for (int curEye = 0; curEye < OpenVR::EYE_LAST; curEye++)
    {
        std::cout << curEye << "------------------------------------------------------------------------" << std::endl;
        glm::mat4 projMat = OVRManager::ovrManager.getProjMatrix(curEye);

        glm::mat4 eye2Head = OVRManager::ovrManager.getEye2HeadMatrix(curEye);


        // Update camera projection matrix:
        glm::mat4 ovrProjMat = projMat * glm::inverse(eye2Head);
#ifdef APP_VERBOSE   
        std::cout << "Eye " << curEye << " proj matrix: " << glm::to_string(ovrProjMat) << std::endl;
#endif

        // Update camera modelview matrix:
        glm::mat4 ovrModelViewMat = glm::inverse(headPos); // Inverted because this is the camera matrix
#ifdef APP_VERBOSE   
        std::cout << "Eye " << curEye << " modelview matrix: " << glm::to_string(ovrModelViewMat) << std::endl;
#endif


        //Program::programPPL.render();
        Program::programPPL.setMatrix(Program::programPPL.projLoc, ovrProjMat);
        Program::programPPL.setMatrix(Program::programPPL.mvLoc, ovrModelViewMat);
        glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(ovrModelViewMat));
        Program::programPPL.setMatrix(Program::programPPL.normLoc, normalMatrix);

        glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(00.0f, 10.0f, -35.0f));

        /*m = m * glm::rotate(glm::mat4(1.0f), glm::radians((float)-90), glm::vec3(0.0f, 1.0f, 0.0f));
        m = m * glm::rotate(glm::mat4(1.0f), glm::radians((float)-90), glm::vec3(0.0f, 1.0f, 0.0f));
        m = m * glm::rotate(glm::mat4(1.0f), glm::radians((float)-45), glm::vec3(0.0f, 1.0f, 0.0f));*/

        getCurrentCamera()->setMatrix(getCurrentCamera()->getInitial_matrix()*headPos);

        RenderList::renderList.setSKyboxMatrix(ovrProjMat);

        //RenderList::renderList.setAllMatrix(_root);

        // Render into this FBO:
        _fboContainer->get(curEye)->render();
        // Clear the FBO content:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderList::renderList.render();




        //RenderList::renderList.removeAll();

        OVRManager::ovrManager.pass(curEye, _fboContainer->getFboTexId(curEye));
        
    }
    OVRManager::ovrManager.render();
    

    _fboContainer->disable();

    glViewport(0, 0, _dimx, _dimy);




    _fboContainer->render();
}

/**
 * @brief Make the principal loop start
 * 
 */
void GraphicsEngine::start()
{
    // Enter the main FreeGLUT processing loop:
    glutMainLoop();
}

/**
 * @brief Free all resurces related to the loaded scene
 * 
 */
void GraphicsEngine::free()
{
    Texture::free();
    delete(_root);
}

/**
 * @brief Wrapper of the the clear method from Open_GL
 * 
 */
void GraphicsEngine::clear()
{
    // Clear the screen:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(_bgcolor.r, _bgcolor.g, _bgcolor.b, _bgcolor.a);
    
}

/**
 * @brief Wrapper of the the method "glutSwapBuffers" from Open_GL
 * 
 */
void GraphicsEngine::swapBuffer()
{
    // Swap this context's buffer:
    _frames++;
    glutSwapBuffers();
}

/**
 * @brief Add a camer to the render list
 * 
 * @param camera that we need to add in the scene
 */
void GraphicsEngine::setCamera(Camera *camera) {
    RenderList::renderList.add(camera);
    RenderList::renderList.setCurrentCamera(0);
}

/**
 * @brief Setter of an OrthoCamera in the scene
 *  It write string in the screen
 * @param camera 
 */
void GraphicsEngine::setOrthoCamera(OrthoCamera* camera) {
    RenderList::renderList.setOrthoCamera(camera);
}

/**
 * @brief Setter of the camera that the user want to use
 * 
 * @param i is the id of the camera in the RenderList
 */
void GraphicsEngine::setCurrentCamera(int i) {
    RenderList::renderList.setCurrentCamera(i);
}

/**
 * @brief Getter of the camera that the user is currently using
 * 
 * @return Camera* is the pointer to the current camera
 */
Camera* GraphicsEngine::getCurrentCamera()
{
    return RenderList::renderList.getCurrentCamera();
}

/**
 * @brief External method of intialization that wrap some glut option
 *  ! This method must be called before method init()
 * 
 */
void GraphicsEngine::setOption()
{
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
}

/**
 * @brief Setter of a flag of using or not an otrhocamera
 * 
 * @param showOrthoCamera 
 */
void GraphicsEngine::setShowOrthoCamera(bool showOrthoCamera)
{
    RenderList::renderList.setShowOrthoCamera(showOrthoCamera);
}

/**
 * @brief Wrapper of the setter from Open_GL that set a displayCallback
 * 
 * @param call1 is the displayCallback
 */
void GraphicsEngine::setDisplayCallback(void(*call1)())
{
    glutDisplayFunc(call1);
}

/**
 * @brief Wrapper of the setter from Open_GL that set a reshapeCallback
 * 
 * @param call2 is the reshapeCallback
 */
void GraphicsEngine::setReshapeCallback(void(*call2)(int, int))
{
    glutReshapeFunc(call2);
}

/**
 * @brief Wrapper of the setter from Open_GL that set a keyboardCallback
 * 
 * @param call is the keyboardCallback 
 */
void GraphicsEngine::setKeyboardCallback(void (*call)(unsigned char, int, int))
{
    glutKeyboardFunc(call);
}

/**
 * @brief Wrapper of the setter from Open_GL that set a timerCallback
 * 
 * @param time 
 * @param call timerCallback
 * @param value 
 */
void GraphicsEngine::setTimerCallback(int time, void(*call)(int), int value) {
    glutTimerFunc(time, call, value);
}


/**
 * @brief Simple debug callback
 * 
 * @param source 
 * @param type 
 * @param id 
 * @param severity 
 * @param length 
 * @param message 
 * @param userParam 
 */
void __stdcall DebugCallback( GLenum source, GLenum type,  GLuint id, GLenum severity,  GLsizei length,
                                const GLchar* message, GLvoid * userParam)
{
    printf("OpenGL says: %s \n", message);
}

/**
 * @brief Setter of DebugCallback in the OpenGL function for debugging message
 * 
 */
void GraphicsEngine::enableDebugger() {
    // Enable the debug flag during context creation:
    
    glDebugMessageCallback((GLDEBUGPROC) DebugCallback, nullptr);
    // Enable debug notifications:
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    
}

/**
 * @brief Intitializer of the vertexShader and fragmentShader
 * 
 */
LIB_API void GraphicsEngine::initShaders()
{
    setStandardShader();
    setPassthroughShader();
    setSkyboxShader();

}
LIB_API void GraphicsEngine::setStandardShader()
{
    Shader* vertexShader = new Shader();
    Shader* fragmentShader = new Shader();

    vertexShader->loadFromMemory(Shader::TYPE_VERTEX, vertShaderTexture);
    fragmentShader->loadFromMemory(Shader::TYPE_FRAGMENT, fragShaderSpot);

    Program::programPPL.build(vertexShader, fragmentShader);
    Program::programPPL.render();
    Program::programPPL.bind(0, "in_Position");
    Program::programPPL.bind(1, "in_Normal");
    Program::programPPL.bind(2, "in_TexCoord");

    // Get shader variable locations:
    Program::programPPL.projLoc = Program::programPPL.getParamLocation("projection");
    Program::programPPL.mvLoc = Program::programPPL.getParamLocation("modelview");
    Program::programPPL.normLoc = Program::programPPL.getParamLocation("normalMatrix");
}


LIB_API void GraphicsEngine::setPassthroughShader()
{
    // Build passthrough shader:
    Shader*  passthroughVs = new Shader();
    passthroughVs->loadFromMemory(Shader::TYPE_VERTEX, passthroughVertShader);

    Shader*  passthroughFs = new Shader();
    passthroughFs->loadFromMemory(Shader::TYPE_FRAGMENT, passthroughFragShader);

    
    Program::programPT.build(passthroughVs, passthroughFs);
    Program::programPT.render();

    // Bind params:
    Program::programPT.bind(0, "in_Position");
    Program::programPT.bind(2, "in_TexCoord");

    Program::programPT.projLoc = Program::programPT.getParamLocation("projection");
    Program::programPT.mvLoc = Program::programPT.getParamLocation("modelview");
    Program::programPT.ptColorLoc = Program::programPT.getParamLocation("color");
}

/**
 * @brief Intitializer of FBO
 *
 */
void GraphicsEngine::initFbo()
{

   

}



LIB_API void GraphicsEngine::setSkyboxShader()
{
    // Build passthrough shader:
    Shader* skyboxVs = new Shader();
    skyboxVs->loadFromMemory(Shader::TYPE_VERTEX, vertShaderSkybox);

    Shader* skyboxFs = new Shader();
    skyboxFs->loadFromMemory(Shader::TYPE_FRAGMENT, fragShaderSkybox);


    Program::programSB.build(skyboxVs, skyboxFs);
    Program::programSB.render();

    // Bind params:
    Program::programSB.bind(0, "in_Position");

    Program::programSB.projLoc = Program::programSB.getParamLocation("projection");
    Program::programSB.mvLoc = Program::programSB.getParamLocation("modelview");
}
LIB_API void GraphicsEngine::enableWireframe(bool b)
{
    if(b)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GraphicsEngine::enableStereoscopicRender(bool b)
{
    _stereoscopicRender = b;
}
