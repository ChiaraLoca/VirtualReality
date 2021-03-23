#include "UtilRender.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
int UtilRender::getParamLocation(const char* name)
{
	// Safety net:
	if (name == nullptr)
	{
		std::cout << "[ERROR] Invalid params" << std::endl;
		return 0;
	}

	// Return location:
	int r = glGetUniformLocation(glId, name);
	if (r == -1)
		std::cout << "[ERROR] Param '" << name << "' not found" << std::endl;
	return r;


}

 void UtilRender::setMatrix(int param, const glm::mat4& mat)
{
	glUniformMatrix4fv(param, 1, GL_FALSE, glm::value_ptr(mat));
}
 void UtilRender::setFloat(int param, float value)
{
	glUniform1f(param, value);
}
 void UtilRender::setInt(int param, int value)
{
	glUniform1i(param, value);
}
 void UtilRender::setVec3(int param, const glm::vec3& vect)
{
	glUniform3fv(param, 1, glm::value_ptr(vect));
}
 void UtilRender::setVec4(int param, const glm::vec4& vect)
{
	glUniform4fv(param, 1, glm::value_ptr(vect));
}

 void UtilRender::bind(int location, const char* attribName)
{
	glBindAttribLocation(glId, location, attribName);
}