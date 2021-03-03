#include "Vertex.h"

Vertex::Vertex(glm::vec3 vertex, glm::vec4 normal, glm::vec2 texture)
: _vertex {vertex}, _normal {normal}, _texture {texture}
{
}

Vertex::Vertex()
{
}
