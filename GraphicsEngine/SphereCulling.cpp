#include "SphereCulling.h"
#include "PerspectiveCamera.h"



SphereCulling::SphereCulling(float near, float far, glm::vec3 normale)
{
    


   _center =(( normale* far) - (normale * near)) * 0.5f;
    
    _radius = (far-near) / 2;

}
bool SphereCulling::checkIfVisible(Mesh* mesh)
{
    /*bool result;
    glm::vec3 meshCenter = mesh->computeWorldCoordinates()[3];
   
    float distanceBetweenCenters = glm::distance(meshCenter, _center);
    float radiuses = mesh->getBoundingSphereRadius() + _radius;
    if (distanceBetweenCenters > radiuses)
        result = false;
    else
        result = true;
    
    std::cout <<mesh->getName() << "\t" << result <<"\t"<< distanceBetweenCenters << "\t" << radiuses << "---------------------------------------------------------------" << std::endl;
    */return true;
    
}
