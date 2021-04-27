#include "Program.h"

// Glew (include it before GL.h):
#include <GL/glew.h>

// FreeGLUT:
#include <GL/freeglut.h>

Program LIB_API Program::program;

Program::Program()
	:Object{ ObjectType::Program ,"Program"}
{

}

Program::~Program() {
	if (glId)
		glDeleteProgram(glId);

};

bool LIB_API Program::build(Shader* vertexShader, Shader* fragmentShader){
	// Safety net:
	if (vertexShader && vertexShader->type != TYPE_VERTEX)
	{
		std::cout << "[ERROR] Invalid vertex shader passed" << std::endl;
		return false;
	}
	if (fragmentShader && fragmentShader->type != TYPE_FRAGMENT)
	{
		std::cout << " [ERROR] Invalid fragment shader passed" << std::endl;
		return false;
	}

	// Delete if already used:
	if (glId)
	{
		// On reload, make sure it was a program before:
		glDeleteProgram(glId);
	}

	// Create program:
	glId = glCreateProgram();
	if (glId == 0)
	{
		std::cout << "[ERROR] Unable to create program" << std::endl;
		return false;
	}

	// Bind vertex shader:
	if (vertexShader)
		glAttachShader(glId, vertexShader->glId);

	// Bind fragment shader:
	if (fragmentShader)
		glAttachShader(glId, fragmentShader->glId);

	// Link program:
	glLinkProgram(glId);

	// Verify program:
	int status;
	char buffer[MAX_LOGSIZE];
	int length = 0;
	memset(buffer, 0, MAX_LOGSIZE);

	glGetProgramiv(glId, GL_LINK_STATUS, &status);
	glGetProgramInfoLog(glId, MAX_LOGSIZE, &length, buffer);
	if (status == false)
	{
		std::cout << "[ERROR] Program link error:" << buffer << std::endl;
		return false;
	}
	glValidateProgram(glId);
	glGetProgramiv(glId, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cout << "[ERROR] Unable to validate program" << std::endl;
		return false;
	}

	// Done:
	return true;
}

bool LIB_API Program::render(void* data)
{
	// Activate shader:
	if (glId)
		glUseProgram(glId);
	else
	{
		std::cout << "[ERROR] Invalid shader rendered" << std::endl;
		return false;
	}

	// Done:
	return true;
}