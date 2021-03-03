// FreeGLUT:
#include <GL/freeglut.h>

#include "Camera.h"
#include "Util.h"

LIB_API Camera::Camera(std::string name, glm::mat4 matrix, ObjectType type, float nearPlane, float farPlane)
    :Node{ name,matrix,ObjectType::Camera }, _nearPlane{ nearPlane }, _farPlane{ farPlane }, _initial_matrix(matrix)
{

}

void LIB_API Camera::setNearPlane(const float nearPlane)
{
    _nearPlane = nearPlane;
}


void LIB_API Camera::setFarPlane(const float farPlane)
{
    _farPlane = farPlane;
}

void Camera::render()
{
}

glm::mat4 Camera::getInverseMatrix() const
{
    return glm::inverse(computeWorldCoordinates());
}

glm::mat4 Camera::getInitial_matrix() const
{
    return _initial_matrix;
}

void Camera::setInitial_matrix(glm::mat4 matrix)
{
    _initial_matrix = matrix;
}

void Camera::reset()
{
    setMatrix(_initial_matrix);
}




