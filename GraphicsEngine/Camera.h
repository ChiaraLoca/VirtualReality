#pragma once
#include "Node.h"

class LIB_API Camera : public Node
{
protected:
    int _width;
    int _height;
    float _nearPlane;
    float _farPlane;
    glm::mat4 _head;
    glm::mat4 _initial_matrix;
    //glm::mat4 _view_matrix;
    

public:
    glm::mat4 _view_matrix;

    Camera(std::string name, glm::mat4 matrix, ObjectType type, float nearPlane, float farPlane);
    void setNearPlane(const float nearPlane);
    void setFarPlane(const float farPlane);
    float getNearPlane();
    float getFarPlane();

    virtual void render();
    virtual glm::mat4 getInverseMatrix() const;
    glm::mat4 getInitial_matrix() const;
    glm::mat4 getHead_matrix() const;
    void setInitial_matrix(glm::mat4 matrix);
    void setHead_matrix(glm::mat4 matrix);
    void reset();
};
