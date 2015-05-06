//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "MeshManager.h"

Resource* MeshManager::LoadResource(const string& name, const int type)
{
	//if we have already loaded the Mesh resource, then return that
	for (auto m : loadedResources)
	{
		if (m->name.compare(name) == 0)
			return m;
	}

	//otherwise attempt to load it
	stringstream s;
	s << "Meshes/" << name;
	Mesh* m = Mesh::LoadMeshFile(s.str());
	MeshResource* mr = new MeshResource();
	mr->mesh = m;
	mr->name = name;
	mr->failedToLoad = (m == NULL);
	loadedResources.push_back(mr);

	return mr;
}