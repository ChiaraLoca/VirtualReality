#pragma once
#include "Vertex.h"
class Face
{
private:

public:
	Vertex _v1;
	Vertex _v2;
	Vertex _v3;
	Face(Vertex v1, Vertex v2, Vertex v3);
};

