#pragma once

// C/C++:
#include <iostream>  
#include <string>

#include "Object.h"
#include "Util.h"
#include "Node.h"
#include "RenderList.h"
#include "FboContainer.h"

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
	FboContainer* _fboContainer;
	void enableDebugger();
	void initShaders();
	void initFbo();


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
	void resize();
	void setStandardShader();
	void setPassthroughShader();
	

	const char* vertShaderEasy = R"(
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

	const char* fragShaderEasy = R"(
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

	/////////////////////////////////////////////////////////

	const char* vertShader = R"(
	   #version 440 core
			// Uniforms:
			uniform mat4 projection;
			uniform mat4 modelview;
			uniform mat3 normalMatrix; // Inverse-transpose
			// Attributes:
			layout(location = 0) in vec3 in_Position;
			layout(location = 1) in vec3 in_Normal;
			// Varying:
			out vec4 fragPos; // In eye coordinates
			out vec3 normal;
			void main(void)
			{
				fragPos = modelview * vec4(in_Position, 1.0f);
				gl_Position = projection * fragPos;
				normal =  normalMatrix * in_Normal;
			}
		)";

	const char* fragShader = R"(
	   #version 440 core
			// Varying variables from the vertex shader:
			in vec4 fragPos;
			in vec3 normal;
			out vec4 fragOutput;
			// Material properties:
			uniform vec3 matEmission;
			uniform vec3 matAmbient;
			uniform vec3 matDiffuse;
			uniform vec3 matSpecular;
			uniform float matShininess;

			// Light properties:
			uniform vec3 lightPos; // In eye coordinates
			uniform vec3 lightAmbient;
			uniform vec3 lightDiffuse;
			uniform vec3 lightSpecular;

			void main(void)
				{
				// Emission and ambient:
				vec3 fragColor = matEmission + matAmbient * lightAmbient;
				// Diffuse term:
				vec3 _normal = normalize(normal);
				vec3 lightDir = normalize(lightPos - fragPos.xyz);
				float nDotL = dot(lightDir, _normal);
				if (nDotL > 0.0f) {
					fragColor += matDiffuse * nDotL * lightDiffuse;
					// Specular term:
					vec3 halfVector = normalize(lightDir + normalize(-fragPos.xyz));
					float nDotHV = dot(_normal, halfVector);
					fragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecular;
				}

				fragOutput = vec4(fragColor, 1.0f);
			}
		)";
	const char* fragShaderMultiLight = R"(				
	   #version 440 core 
			// Varying variables from the vertex shader:
			in vec4 fragPos;
			in vec3 normal;
			out vec4 fragOutput;
			// Material properties:
			uniform vec3 matEmission;
			uniform vec3 matAmbient;
			uniform vec3 matDiffuse;
			uniform vec3 matSpecular;
			uniform float matShininess;

			// Light properties:
			#define MAX_LIGHT 8
			
			uniform vec3 lightPos[MAX_LIGHT]; // In eye coordinates
			uniform vec3 lightAmbient[MAX_LIGHT];
			uniform vec3 lightDiffuse[MAX_LIGHT];
			uniform vec3 lightSpecular[MAX_LIGHT];
			
			vec3 CalcOmniLight(int index)
			{
				vec3 internalFragColor = matEmission + matAmbient * lightAmbient[index];
				// Diffuse term:
				vec3 _normal = normalize(normal);
				vec3 lightDir = normalize(lightPos[index] - fragPos.xyz);
				float nDotL = dot(lightDir, _normal);
				if (nDotL > 0.0f) {
					internalFragColor += matDiffuse * nDotL * lightDiffuse[index];
					// Specular term:
					vec3 halfVector = normalize(lightDir + normalize(-fragPos.xyz));
					float nDotHV = dot(_normal, halfVector);
					internalFragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecular[index];
				}
				return internalFragColor;
			} 

			void main()
			{		
				vec3 result;
				/*if(lightDiffuse[0][0]<0.7 && lightDiffuse[0][0]>0.5)
					fragOutput = vec4(0.8f);*/
					
				for(int i = 0; i < MAX_LIGHT; i++){
					result += CalcOmniLight(i);
				}
    
				fragOutput = vec4(result, 1.0f);
			}
		)";

	///////////////////////////////////////////////////////
	const char* vertShaderTexture = R"(
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

	const char* fragShaderTexture = R"(
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
			uniform vec3 lightPos; // In eye coordinates
			uniform vec3 lightAmbient;
			uniform vec3 lightDiffuse;
			uniform vec3 lightSpecular;

			// Texture mapping:
			layout(binding = 0) uniform sampler2D texSampler;

			void main(void)
				{
				// Texture element:
				vec4 texel = texture(texSampler, texCoord);

				// Emission and ambient:
				vec3 fragColor = matEmission + matAmbient * lightAmbient;
				// Diffuse term:
				vec3 _normal = normalize(normal);
				vec3 lightDir = normalize(lightPos - fragPos.xyz);
				float nDotL = dot(lightDir, _normal);
				if (nDotL > 0.0f) {
					fragColor += matDiffuse * nDotL * lightDiffuse;
					// Specular term:
					vec3 halfVector = normalize(lightDir + normalize(-fragPos.xyz));
					float nDotHV = dot(_normal, halfVector);
					fragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecular;
				}

				fragOutput = texel*vec4(fragColor, 1.0f);
			}
		)";

	/////////////////////////////////////////////////////////////////////////////////////////
	const char* fragShaderTextureMultiLight = R"(
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
			
			uniform vec3 lightPos[MAX_LIGHT]; // In eye coordinates
			uniform vec3 lightAmbient[MAX_LIGHT];
			uniform vec3 lightDiffuse[MAX_LIGHT];
			uniform vec3 lightSpecular[MAX_LIGHT];

			// Texture mapping:
			layout(binding = 0) uniform sampler2D texSampler;

			vec3 CalcOmniLight(int index)
			{
				vec3 internalFragColor = matEmission + matAmbient * lightAmbient[index];
				// Diffuse term:
				vec3 _normal = normalize(normal);
				vec3 lightDir = normalize(lightPos[index] - fragPos.xyz);
				float nDotL = dot(lightDir, _normal);
				if (nDotL > 0.0f) {
					internalFragColor += matDiffuse * nDotL * lightDiffuse[index];
					// Specular term:
					vec3 halfVector = normalize(lightDir + normalize(-fragPos.xyz));
					float nDotHV = dot(_normal, halfVector);
					internalFragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecular[index];
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
				}

				fragOutput = texel*vec4(result, 1.0f);

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
		//vec4 verde =  vec4(1.0f, 0.0f, 1.0f,0.5f);
        fragOutput = color * texel;       
		//fragOutput = verde * texel;    
   }
)";

	const char* fragShaderSpot = R"(
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
				lightCutoffSpot[0];
				lightDirectionSpot[0];
				
				vec3 internalFragColor = matEmission + matAmbient * lightAmbientSpot[index];

				// Diffuse term:
				vec3 _normal = normalize(normal);
				vec3 lightDir = normalize(lightPosSpot[index] - fragPos.xyz);
				float nDotL = dot(lightDir, _normal);
				if (nDotL > 0.0f) {
					internalFragColor += matDiffuse * nDotL * lightDiffuseSpot[index];
					// Specular term:
					vec3 halfVector = normalize(lightDir + normalize(-fragPos.xyz));
					float nDotHV = dot(_normal, halfVector);
					internalFragColor += matSpecular * pow(nDotHV, matShininess) * lightSpecularSpot[index];
				}

				//internalFragColor = internalFragColor * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - lightCutoffSpot[index]));
 
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





};


