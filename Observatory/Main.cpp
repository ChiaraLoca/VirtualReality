#include "GraphicsEngine.h"
// C/C++:
#include <iostream>
#include <string>
#include <vector>
#include <string>

#include "Mesh.h"
#include "Node.h"
#include "Object.h"
#include "OmniLight.h"
#include "OVOReader.h"
#include "Test.h"
#include "RenderList.h"
#include "PerspectiveCamera.h"
#include <OrthoCamera.h>
#include "UtilClient.h"


OrthoCamera* orthoCamera;
Node* root;
char titolo[] = "Osservatorio";
GraphicsEngine _graphicsEngine(titolo);
bool observatoryOpen = true;
int frames=0;

float domeRotation = 0.0f;
const float domeSpeed = 1.0f;
const float hatchSpeed = 0.02f;
const float lightSpeed = 1.0f;
const float cameraSpeed = 1.0f;

const float telescopeSpeed = 0.1f;
const float maxOutTelescope = 8.0f;
float currentOutTelescope = 0.0f;

float maxOpening = 0.94f;
float currentOpening = 0.94f;
bool showLaser = true;
bool hasToBeOff = false;
int _width = 0;
int _height = 0;
bool isHatchOnOpen = true;
bool showOrthoText = true;




void displayCall() {

    _graphicsEngine.clear();
    _graphicsEngine.setOption();
    _graphicsEngine.render();
    _graphicsEngine.swapBuffer();
    _graphicsEngine.refresh();
}

void reshapeCall(int width, int height)
{
    _width = width;
    _height = height;
    ((PerspectiveCamera*) _graphicsEngine.getCurrentCamera())->setWidthHeight(width, height);
	orthoCamera->setWidthHeight(width, height);
}

bool doShowLaser(bool show) {
    Node* laser = _graphicsEngine.getNodeByName("FascioLaser");
    if (show) {
        laser->setMatrix(laser->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0, 200.0f, 0.0f)));
        return false;
    }
    else {
        laser->setMatrix(laser->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0, -200.0f, 0.0f)));
        return true;
    }
}

// Callback for animation
void keyboardCallback(unsigned char key, int mouseX, int mouseY)
{
    Node* dome = _graphicsEngine.getNodeByName("CupolaOsservatorio");
    Node* dynamicLight = _graphicsEngine.getNodeByName("LuceDinamica");

    switch (key)
    {

        // on off laser
        case ' ':
        if (currentOpening > 0.0f) {
            showLaser = doShowLaser(showLaser);
            hasToBeOff = !showLaser;
        }
        break;

        // move spot light
        case 'a':
            dynamicLight->setMatrix(dynamicLight->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(lightSpeed), glm::vec3(1.0f, 0.0f, 0.0f)));
            break;
        case 'd':
            dynamicLight->setMatrix(dynamicLight->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(-lightSpeed), glm::vec3(1.0f, 0.0f, 0.0f)));
            break;
        case 'w':
            dynamicLight->setMatrix(dynamicLight->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(lightSpeed), glm::vec3(0.0f, 0.0f, 1.0f)));
            break;
        case 's':
            dynamicLight->setMatrix(dynamicLight->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(-lightSpeed), glm::vec3(0.0f, 0.0f, 1.0f)));
            break;

        // move current camera - A Peternier non piace :(
        case 'j':
            _graphicsEngine.getCurrentCamera()->setMatrix(_graphicsEngine.getCurrentCamera()->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(cameraSpeed), glm::vec3(0.0f, 1.0f, 0.0f)));
            break;
        case 'l':
            _graphicsEngine.getCurrentCamera()->setMatrix(_graphicsEngine.getCurrentCamera()->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(-cameraSpeed), glm::vec3(0.0f, 1.0f, 0.0f)));
            break;
        case 'i':
            _graphicsEngine.getCurrentCamera()->setMatrix(_graphicsEngine.getCurrentCamera()->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(cameraSpeed), glm::vec3(1.0f, 0.0f, 0.0f)));
            break;
        case 'k':
            _graphicsEngine.getCurrentCamera()->setMatrix(_graphicsEngine.getCurrentCamera()->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(-cameraSpeed), glm::vec3(1.0f, 0.0f, 0.0f)));
            break;
        case 'u':
            _graphicsEngine.getCurrentCamera()->setMatrix(_graphicsEngine.getCurrentCamera()->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -cameraSpeed)));
            break;
        case 'o':
            _graphicsEngine.getCurrentCamera()->setMatrix(_graphicsEngine.getCurrentCamera()->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, cameraSpeed)));
            break;

        // rotate dome
        case 't':
            dome->setMatrix(dome->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(domeSpeed), glm::vec3(0.0f, 1.0f, 0.0f)));
            break;
        case 'r':
            dome->setMatrix(dome->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(-domeSpeed), glm::vec3(0.0f, 1.0f, 0.0f)));
            break;

            // Open close hatch
        case 'h':
            isHatchOnOpen = !isHatchOnOpen;
            break;

        case 'v':
            // show hide text
            showOrthoText = !showOrthoText;
            _graphicsEngine.setShowOrthoCamera(showOrthoText);
            break;

       // Camera choose
        case '1':
            _graphicsEngine.setCurrentCamera(0);
            reshapeCall(_width, _height);
            break;
        case '2':
            _graphicsEngine.setCurrentCamera(1);
            reshapeCall(_width, _height);
            break;
        case '3':
            _graphicsEngine.setCurrentCamera(2);
            reshapeCall(_width, _height);
            break;
        case '4':
            _graphicsEngine.setCurrentCamera(3);
            reshapeCall(_width, _height);
            break;
        case 'x':
            _graphicsEngine.getCurrentCamera()->reset();
            reshapeCall(_width, _height);
            break;
    }

    // Force rendering refresh:
    _graphicsEngine.refresh();

}


int numCallFunction = 0;

// this function is called every 10 ms
void timerCallback(int value)
{
    ++numCallFunction;
    if (numCallFunction == 100){
	    // Update values:
	    frames = _graphicsEngine.getFrames();
	    orthoCamera->setFps(frames);
	    _graphicsEngine.setFrames(0);
        numCallFunction = 0;
    }

    Node* rightHatch = _graphicsEngine.getNodeByName("PortelloDX");
    Node* leftHatch = _graphicsEngine.getNodeByName("PortelloSX");
    Node* telescope = _graphicsEngine.getNodeByName("Telescopio");

    // Control for open
    if (currentOpening < maxOpening && isHatchOnOpen)
    {
        leftHatch->setMatrix(leftHatch->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(hatchSpeed, 0.0f, -hatchSpeed / 1.5)));
        rightHatch->setMatrix(rightHatch->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-hatchSpeed, 0.0f, hatchSpeed / 1.5)));
        if (currentOpening < 0.0f && !hasToBeOff)
            showLaser = doShowLaser(showLaser);
        currentOpening += hatchSpeed;
    }

    // Control for closing
    if (currentOpening >= 0.0f && !isHatchOnOpen)
    {
        leftHatch->setMatrix(leftHatch->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-hatchSpeed, 0.0f, hatchSpeed / 1.5)));
        rightHatch->setMatrix(rightHatch->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(hatchSpeed, 0.0f, -hatchSpeed / 1.5)));
        currentOpening -= hatchSpeed;
        if (currentOpening < 0.0f && !hasToBeOff)
            showLaser = doShowLaser(showLaser);
    }

    //Control for telescope
    if (isHatchOnOpen && currentOutTelescope < maxOutTelescope) {
        currentOutTelescope += telescopeSpeed;
        telescope->setMatrix(telescope->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-telescopeSpeed / 10, telescopeSpeed, -0.012)));
    }

    if (!isHatchOnOpen && currentOutTelescope >= 0.0f) {

        currentOutTelescope -= telescopeSpeed;
        telescope->setMatrix(telescope->getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(telescopeSpeed / 10, -telescopeSpeed, 0.012)));

    }

    // Register the next update
    _graphicsEngine.setTimerCallback(10, timerCallback, 0);

}



/*void test()
{
    Test test;
    test.runTest();
}*/
void observatoryScene()
{
    if (_graphicsEngine.initialize() < 0)
        return;
    UtilClient util{};
    std::string s{ util.buildContext("../OVOResources","/") };

    OVOReader reader{ s };
    root = reader.load("MultipleOmni.OVO");

    _graphicsEngine.setRoot(root);

    //BACKGROUND
    _graphicsEngine.setBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f);

    //CAMERE

    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 30.0f, -100.0f));
    m = m * glm::rotate(glm::mat4(1.0f), glm::radians((float)180), glm::vec3(0.0f, 1.0f, 0.0f));
    PerspectiveCamera* c1 = new PerspectiveCamera("Camera1", m, 1, 400);

    m = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 100.0f, 0.0f));
    m = m * glm::rotate(glm::mat4(1.0f), glm::radians((float)270), glm::vec3(1.0f, 0.0f, 0.0f));
    PerspectiveCamera* c2 = new PerspectiveCamera("Camera2", m, 1, 200);

    m = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, 10.0f, -40.0f));
    m = m * glm::rotate(glm::mat4(1.0f), glm::radians((float)135), glm::vec3(0.0f, 1.0f, 0.0f));
    PerspectiveCamera* c3 = new PerspectiveCamera("Camera3", m, 1, 200);

    m = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 30.0f, 100.0f));
    PerspectiveCamera* c4 = new PerspectiveCamera("Camera4", m, 1, 200);

    orthoCamera = new OrthoCamera("Ortho", glm::mat4(1));
    _graphicsEngine.setOrthoCamera(orthoCamera);

    _graphicsEngine.setCamera(c1);
    _graphicsEngine.setCamera(c2);
    _graphicsEngine.setCamera(c3);
    _graphicsEngine.setCamera(c4);
    _graphicsEngine.setCurrentCamera(0);


    _graphicsEngine.setDisplayCallback(displayCall);
    _graphicsEngine.setReshapeCallback(reshapeCall);
    _graphicsEngine.setKeyboardCallback(keyboardCallback);
    _graphicsEngine.setTimerCallback(10, timerCallback, 0);
    _graphicsEngine.start();

    _graphicsEngine.free();
}
int main()
{
	//test();

    UtilClient util{};
    util.infoText();

    observatoryScene();
}

