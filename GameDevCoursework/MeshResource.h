#pragma once
#include "GraphicsCode\Mesh.h"
#include "Resource.h"

class MeshResource : public Resource
{
public:

	MeshResource() {}
	~MeshResource() { delete mesh; }

	Mesh* mesh;
};

