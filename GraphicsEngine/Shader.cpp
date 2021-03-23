// Header:
#include "shader.h"

Shader::Shader() : type(TYPE_UNDEFINED){}
Shader::~Shader()
{
	if (glId)
		glDeleteShader(glId);
			

		
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Loads and compiles a vertex or fragment shader from source code stored in memory.
 * @param subtype subtype of shader (vertex or fragment)
 * @param data pointer to the string containing the source code
 * @return true/false on success/failure
 */
bool Shader::loadFromMemory(int type, const char* data)
{
	// Safety net:
	if (data == nullptr)
	{
		std::cout << "[ERROR] Invalid params" << std::endl;
		return false;
	}

	// Check kind:
	int glKind = 0;
	switch (type)
	{
		////////////////////
	case TYPE_VERTEX: //
		glKind = GL_VERTEX_SHADER;
		break;

		//////////////////////
	case TYPE_FRAGMENT: //
		glKind = GL_FRAGMENT_SHADER;
		break;

		///////////
	default: //
		std::cout << "[ERROR] Invalid kind" << std::endl;
		return false;
	}

	// Destroy if already loaded:
	if (glId)
		glDeleteShader(glId);
		

	// Load program:
	glId = glCreateShader(glKind);
	if (glId == 0)
	{
		std::cout << "[ERROR] Unable to create shader object" << std::endl;
		return false;
	}
	glShaderSource(glId, 1, (const char**)&data, NULL);
	glCompileShader(glId);

	// Verify shader:
	int status;
	char buffer[MAX_LOGSIZE];
	int length = 0;
	memset(buffer, 0, MAX_LOGSIZE);

	glGetShaderiv(glId, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(glId, MAX_LOGSIZE, &length, buffer);
	if (status == false)
	{
		std::cout << "[ERROR] Shader not compiled: " << buffer << std::endl;
		return false;
	}

	// Update values:
	this->type = type;

	// Done:
	return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Loads and compiles a vertex, pixel or geometry shader from a specified source text file.
 * @param subtype subtype of shader (pixel, vertex, geometry or program shader)
 * @param filename text file containing the vertex shader code
 * @return true/false on success/failure
 */
bool Shader::loadFromFile(int type, const char* filename)
{
	// Safety net:
	if (filename == nullptr)
	{
		std::cout << "[ERROR] Invalid params" << std::endl;
		return false;
	}

	// Open file:
	FILE* dat = fopen(filename, "rt");
	if (dat == nullptr)
	{
		std::cout << "[ERROR] Unable to open file" << std::endl;
		return false;
	}

	// Get file length:
	unsigned int length;
	fseek(dat, 0L, SEEK_END);
	length = ftell(dat);
	fseek(dat, 0L, SEEK_SET);

	// Read code:
	char* content = nullptr;
	if (length > 0)
	{
		content = new char[sizeof(char) * (length + 1)];
		length = (unsigned int)fread(content, sizeof(char), length, dat);
		content[length] = '\0';
	}
	fclose(dat);

	// Load from memory then:
	bool result = loadFromMemory(type, content);

	// Clean:
	delete[] content;

	// Done:
	return result;
}



