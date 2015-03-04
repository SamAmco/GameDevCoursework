//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Mesh.h"
#include <string>
#include <map>

using namespace std;

//Manages Mesh loading and the memory used by the meshes
class MeshManager
{
public:

	//singleton getter
	static MeshManager& getInstance()
	{
		static MeshManager instance;
		return instance;
	}

	Mesh* LoadMesh(const string);
	void UnloadMeshes();

	~MeshManager();

private:
	//These parts enforce singleton constraints
	MeshManager();
	MeshManager(MeshManager const&) = delete;
	void operator=(MeshManager const&) = delete;

	//Store a map of already loaded meshes
	map<string, Mesh*> loadedMeshes;
};

