#pragma once
#define LIB_NAME      "Graphics Engine V1"  
#define LIB_VERSION   1                             


#ifdef _WINDOWS 
#ifdef GRAPHICSENGINE_EXPORTS 
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif      	
#else // Under Linux
#define LIB_API  
#endif

#ifdef _WINDOWS
#define SEPARATOR "\\"
#else
#define SEPARATOR "/"
#endif


// GLM:   
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>



