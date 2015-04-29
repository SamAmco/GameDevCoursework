//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Mesh.h"
#include <string>
#include <fstream>
#include <vector>
#include "ResourceManager.h"
#include "MeshResource.h"

using namespace std;

//Manages Mesh loading and the memory used by the meshes
class MeshManager : public ResourceManager
{
public:

	Resource* LoadResource(const string& name, const int type = 0);

	//singleton getter
	static MeshManager& getInstance()
	{
		static MeshManager instance;
		return instance;
	}

	~MeshManager() { UnloadAllResources(); }

private:
	//These parts enforce singleton constraints
	MeshManager(){};
};

