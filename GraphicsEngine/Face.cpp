#include "Face.h"

/**
 * @brief Construct a new Face:: Face object
 * 
 * @param v1 is the first vertex of the face
 * @param v2 is the second vertex of the face
 * @param v3 is the third vertex of the face
 */
Face::Face(Vertex v1, Vertex v2, Vertex v3)
	: _v1{v1}, _v2{v2}, _v3{v3}
{
}
