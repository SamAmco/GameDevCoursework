#include "stdafx.h"
#include "MeshManager.h"
#include <fstream>


MeshManager::MeshManager()
{
	loadedMeshes = map<string, Mesh*>();
}

Mesh* MeshManager::LoadMesh(string path)
{
	std::map<string, Mesh*>::const_iterator i = loadedMeshes.find(path);
	if (i != loadedMeshes.end())
		return (*i).second;

	return Mesh::LoadMeshFile(path);
}


MeshManager::~MeshManager()
{
}
