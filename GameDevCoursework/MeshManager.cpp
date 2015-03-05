//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "MeshManager.h"
#include <fstream>


MeshManager::MeshManager()
{
	loadedMeshes = map<string, Mesh*>();
}

//delete all the Mesh objects from the heap and clear the map
void MeshManager::UnloadMeshes()
{
	map<string, Mesh*>::const_iterator i = loadedMeshes.begin();
	while (i != loadedMeshes.end())
	{
		Mesh* m = i->second;
		cout << "deleting mesh " << i->first << "\n";
		delete m;
		++i;
	}
	loadedMeshes.clear();
}

Mesh* MeshManager::LoadMesh(string path)
{
	//if we have already loaded the Mesh object, then return that
	std::map<string, Mesh*>::const_iterator i = loadedMeshes.find(path);
	if (i != loadedMeshes.end())
		return (*i).second;

	//otherwise attempt to load it
	Mesh* m = Mesh::LoadMeshFile(path);
	loadedMeshes.insert(std::pair<string, Mesh*>(path, m));

	return m;
}


MeshManager::~MeshManager()
{
	//Just in case
	UnloadMeshes();
}
