// FreeGLUT:
#include <GL/freeglut.h>

#include "Camera.h"
#include "Util.h"

/**
 * @brief Constructor of the camera
 * 
 * @param name of the camera in the .OVO file
 * @param matrix of tha camera. Is in object coordinate
 * @param type of the object (in this case CAMERA)
 * @param nearPlane of the camera. The object that are closer than this plane are not rendered
 * @param farPlane  of the camera. The object that are farther than this plane are not rendered
 */
LIB_API Camera::Camera(std::string name, glm::mat4 matrix, ObjectType type, float nearPlane, float farPlane)
    :Node{ name,matrix,ObjectType::Camera }, _nearPlane{ nearPlane }, _farPlane{ farPlane }, _initial_matrix(matrix)
{

}

/**
 * @brief setter of the near plane
 * 
 * @param nearPlane is the new value of the near plane
 */
void LIB_API Camera::setNearPlane(const float nearPlane)
{
    _nearPlane = nearPlane;
}

/**
 * @brief setter of the far plane
 * 
 * @param nearPlane is the new value of the far plane
 */
void LIB_API Camera::setFarPlane(const float farPlane)
{
    _farPlane = farPlane;
}

/**
 * @brief Render of the camera.
 *  It does nothing because the room does not have to be rendered.
 * 
 */
void Camera::render()
{
}

/**
 * @brief Calculate the inverse of the camera matrix
 *   Used to calculate the eye coordinate
 * 
 * @return inverse of the world coordinate 
 */
glm::mat4 Camera::getInverseMatrix() const
{
    
    return glm::inverse(computeWorldCoordinates());
}

/**
 * @brief Getter of the initial matrix
 *  
 * 
 * @return _initial_matrix is the position of the camera before applying the tranformation
 */
glm::mat4 Camera::getInitial_matrix() const
{
    return _initial_matrix;
}
glm::mat4 Camera::getHead_matrix() const
{
    return _head;
}

/**
 * @brief Setter of the initial matrix
 * 
 * @param matrix is the position of the camera before applying the tranformation
 */
void Camera::setInitial_matrix(glm::mat4 matrix)
{
    _initial_matrix = matrix;
}void Camera::setHead_matrix(glm::mat4 matrix)
{
    _head = matrix;
}

/**
 * @brief Make the camera come back at its initial position (before appling the tranformation)
 * 
 */
void Camera::reset()
{
    setMatrix(_initial_matrix);
}




