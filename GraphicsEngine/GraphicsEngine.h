#pragma once

// C/C++:
#include <iostream>  
#include <string>

#include "Object.h"
#include "Util.h"
#include "Node.h"
#include "RenderList.h"
#include "FboContainer.h"
#include "Skybox.h"


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
	bool _stereoscopicRender = true;
	Node* _root; // contains a reference to the root of the scene
	FboContainer* _fboContainer;
	Skybox* _skybox;
	void enableDebugger();
	void initShaders();
	void initFbo();
	void standardRender();
	void stereoscopicRender();
	


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
	void setDisplayCallback(void(*call1)());
	void setReshapeCallback(void(*call2)(int, int));
	void setKeyboardCallback(void (*call)(unsigned char, int, int));
	void setTimerCallback(int time,void(*call1)(int),int value);
	void resize();
	void setStandardShader();
	void setPassthroughShader();
	void setSkyboxShader();
	void enableWireframe(bool b);
	void enableStereoscopicRender(bool b);

	const char* perPixelLightingFragmentShader = R"(
	   #version 440 core
			// Varying variables from the vertex shader:
			in vec4 fragPos;
			in vec3 normal;
			in vec2 texCoord;
			out vec4 fragOutput;
			
			// Material properties:
			uniform vec3 matEmission;
			uniform vec3 matAmbient;
			uniform vec3 matDiffuse;
			uniform vec3 matSpecular;
			uniform float matShininess;

			// Light properties:
			#define MAX_LIGHT 8
			
			// Define vector for omniLight
			uniform vec3 lightPosOmni[MAX_LIGHT]; // In eye coordinates
			uniform vec3 lightAmbientOmni[MAX_LIGHT];
			uniform vec3 lightDiffuseOmni[MAX_LIGHT];
			uniform vec3 lightSpecularOmni[MAX_LIGHT];

			// Define vector for spotLight
			uniform float lightCutoffSpot[MAX_LIGHT];
			uniform vec3 lightDirectionSpot[MAX_LIGHT];

			uniform vec3 lightPosSpot[MAX_LIGHT]; // In eye coordinates
			uniform vec3 lightAmbientSpot[MAX_LIGHT];
			uniform vec3 lightDiffuseSpot[MAX_LIGHT];
			uniform vec3 lightSpecularSpot[MAX_LIGHT];	

			// Texture mapping:
			layout(binding = 0) uniform sampler2D texSampler;

			vec3 CalcOmniLight(int index)
			{
				vec3 internalFragColor = matEmission + matAmbient * lightAmbientOmni[index];
				// Diffuse term:
				vec3 _normal = normalize(normal);
				vec3 lightDir = normalize(lightPosOmni[index] - fragPos.xyz);
				float nDotL = dot(lightDir, _normal);
				if (nDotL > 0.0f) {
					internalFragColor += matDiffuse * nDotL * lightDiffuseOmni[index];
					// Specular term:
					vec3 halfVector = normalize(lightDir + normalize(-fragPos.xyz));
					float nDotHV = dot(_normal, halfVector);
					internalFragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecularOmni[index];
				}
				return internalFragColor;
			}

			vec3 CalcSpotLight(int index)
			{
				// Diffuse term:
				vec3 _normal = normalize(normal);
				vec3 lightDir = normalize(lightPosSpot[index] - fragPos.xyz);
				float nDotL = dot(lightDir, _normal);

				vec3 internalFragColor = matEmission + matAmbient * lightAmbientSpot[index];
				float theta = dot(lightDir, normalize(lightDirectionSpot[index]));
    
				if(theta > lightCutoffSpot[index]) {       
					if (nDotL > 0.0f) {
						internalFragColor += matDiffuse * nDotL * lightDiffuseSpot[index];
						// Specular term:
						vec3 halfVector = normalize(lightDir + normalize(-fragPos.xyz));
						float nDotHV = dot(_normal, halfVector);
						internalFragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecularSpot[index];
					}
				}
				return internalFragColor;
			}

			void main(void)
			{
				// Texture element:
				vec4 texel = texture(texSampler, texCoord);

				vec3 result;	
				for(int i = 0; i < MAX_LIGHT; i++){
					result += CalcOmniLight(i);
					result += CalcSpotLight(i);
				}

				fragOutput = texel*vec4(result, 1.0f);

			}
		)";

	const char* vertShaderSkybox = R"(
   #version 440 core

   uniform mat4 projection;
   uniform mat4 modelview;

   layout(location = 0) in vec3 in_Position;      

   out vec3 texCoord;

   void main(void)
   {
		texCoord = in_Position;
		gl_Position = projection * modelview * vec4(in_Position, 1.0f);            
   }
)";

	const char* fragShaderSkybox = R"(
   #version 440 core
   
   in vec3 texCoord;
   
   // Texture mapping (cubemap):
   layout(binding = 0) uniform samplerCube cubemapSampler;

   out vec4 fragOutput;

   void main(void)
   {       
      fragOutput = texture(cubemapSampler, texCoord);
   }
)";

	const char* perPixelLightingVertexShader = R"(
	#version 440 core
		// Uniforms:
		uniform mat4 projection;
		uniform mat4 modelview;
		uniform mat3 normalMatrix; // Inverse-transpose

		// Attributes:
		layout(location = 0) in vec3 in_Position;
		layout(location = 1) in vec3 in_Normal;
		layout(location = 2) in vec2 in_TexCoord;
		// Varying:
		out vec4 fragPos; // In eye coordinates
		out vec3 normal;
		out vec2 texCoord; 
		void main(void)
		{
			texCoord = in_TexCoord;
			fragPos = modelview * vec4(in_Position, 1.0f);
			gl_Position = projection * fragPos;
			normal = normalMatrix * in_Normal;
		}
	)";

	

	

	const char* passthroughVertShader = R"(
   #version 440 core

   // Uniforms:
   uniform mat4 projection;
   uniform mat4 modelview;   

   // Attributes:
   layout(location = 0) in vec2 in_Position;   
   layout(location = 2) in vec2 in_TexCoord;

   // Varying:   
   out vec2 texCoord;

   void main(void)
   {      
      gl_Position = projection * modelview * vec4(in_Position, 0.0f, 1.0f);    
      texCoord = in_TexCoord;
   }
)";

	const char* passthroughFragShader = R"(
   #version 440 core
   
   in vec2 texCoord;
   
   uniform vec4 color;

   out vec4 fragOutput;   

   // Texture mapping:
   layout(binding = 0) uniform sampler2D texSampler;

   void main(void)   
   {  
      // Texture element:
      vec4 texel = texture(texSampler, texCoord);      
      
      // Final color:
      fragOutput = color * texel;       
		
   }
)";






};


