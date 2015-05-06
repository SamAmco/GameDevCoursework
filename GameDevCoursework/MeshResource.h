//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Mesh.h"
#include "Resource.h"

//Stores and destroys a mesh
class MeshResource : public Resource
{
public:

	MeshResource() {}
	~MeshResource() { delete mesh; }

	Mesh* mesh;
};

