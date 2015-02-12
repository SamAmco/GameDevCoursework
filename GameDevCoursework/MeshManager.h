#pragma once
#include "GraphicsCode\Mesh.h"
#include <string>
#include <map>

using namespace std;

class MeshManager
{
public:

	//singleton getter
	static MeshManager& getInstance()
	{
		static MeshManager instance;

		return instance;
	}

	Mesh* LoadMesh(string);
	void UnloadMeshes();

	~MeshManager();

private:
	//These parts enforce singleton constraints
	MeshManager();
	MeshManager(MeshManager const&) = delete;
	void operator=(MeshManager const&) = delete;

	map<string, Mesh*> loadedMeshes;
};

