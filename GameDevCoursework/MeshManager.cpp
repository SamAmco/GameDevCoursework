#include "stdafx.h"
#include "MeshManager.h"
#include <fstream>


MeshManager::MeshManager()
{
	loadedMeshes = map<string, Mesh*>();
}

void MeshManager::UnloadMeshes()
{
	map<string, Mesh*>::const_iterator i = loadedMeshes.begin();
	while (i != loadedMeshes.end())
	{
		Mesh* m = i->second;
		cout << "deleting " << i->first << "\n";
		delete m;
		++i;
	}
	loadedMeshes.clear();
}

Mesh* MeshManager::LoadMesh(string path)
{
	std::map<string, Mesh*>::const_iterator i = loadedMeshes.find(path);
	if (i != loadedMeshes.end())
		return (*i).second;

	Mesh* m = Mesh::LoadMeshFile(path);
	loadedMeshes.insert(std::pair<string, Mesh*>(path, m));

	return m;
}


MeshManager::~MeshManager()
{
}
