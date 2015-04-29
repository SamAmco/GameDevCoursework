//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "MeshManager.h"

Resource* MeshManager::LoadResource(const string& name, const int type)
{
	//if we have already loaded the Mesh object, then return that
	for (auto m : loadedResources)
	{
		if (m->name.compare(name) == 0)
			return m;
	}

	//otherwise attempt to load it
	Mesh* m = Mesh::LoadMeshFile(name);
	MeshResource* mr = new MeshResource();
	mr->mesh = m;
	mr->name = name;
	mr->failedToLoad = (m == NULL);
	loadedResources.push_back(mr);

	return mr;
}