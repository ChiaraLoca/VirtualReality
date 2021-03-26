#pragma once

// C/C++:
#include <iostream>  
#include <string>

#include "Object.h"
#include "Util.h"
#include "Node.h"
#include "RenderList.h"

#ifdef _WINDOWS
#include <Windows.h>

// Establishing the entry point of the DLL, necessary for loading the dll at the begin of the process
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved)
{
	// Check use:
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}
#endif

class LIB_API GraphicsEngine
{
private:

	int _windowId;
	glm::vec4 _bgcolor;
	int _dimx;
	int _dimy;
	int _posx;
	int _posy;
	char* _title;
	int _frames;
	Node* _root; // contains a reference to the root of the scene
	void enableDebugger();
	void initShaders();


public:
	GraphicsEngine(char* title, int dimx = 1000, int dimy = 1000, int posx = 100, int posy = 100)
		: _dimx{ dimx }, _dimy{ dimy }, _posx{ posx }, _posy{ posy }, _frames{ 0 }, _title{ title } {}

	int initialize();
	void setBackgroundColor(float r, float g, float b,float a =0);
	void setDimension(float dimx, float dimy);
	void setPosition(float posx, float posy);
	void setTitle(char* title);
	void setRoot(Node* root);
	void setFrames(int frames);
	int getFrames() const;
	Node* getRoot() const;
	Node* getNodeByName(std::string name) const;
	void refresh();
	void render();
	void start();
	void free();
	void clear();
	void setOption();
	void swapBuffer();
	void setCamera(Camera* camera);
	void setCurrentCamera(int i);
	Camera* getCurrentCamera(); 
	void setOrthoCamera(OrthoCamera* camera);
	void setShowOrthoCamera(bool showOrthoCamera);
	void setDisplayCallback(void(*call1)());
	void setReshapeCallback(void(*call2)(int, int));
	void setKeyboardCallback(void (*call)(unsigned char, int, int));
	void setTimerCallback(int time,void(*call1)(int),int value);


	const char* vertShader = R"(
	   #version 440 core

	   uniform mat4 projection;
	   uniform mat4 modelview;

	   layout(location = 0) in vec3 in_Position;
	   layout(location = 1) in vec4 in_Color;

	   out vec3 out_Color;
	   out float dist;

	   void main(void)
	   {
		  gl_Position = projection * modelview * vec4(in_Position, 1.0f);
		  dist = abs(gl_Position.z / 100.0f);
		  out_Color = in_Color.rgb;
	   }
		)";

	////////////////////////////
	const char* fragShader = R"(
	   #version 440 core

	   in  vec3 out_Color;
	   in  float dist;
   
	   out vec4 frag_Output;

	   void main(void)
	   {
			vec3 fog = vec3(1.0f, 1.0f, 1.0f);
			frag_Output = vec4(mix(out_Color, fog, dist), 1.0f);
		}
		)";
};


