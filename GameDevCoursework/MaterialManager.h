//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Shader.h"
#include <string>
#include <vector>
#include <sstream>
#include "ResourceManager.h"
#include "MaterialResource.h"

//Manages Shader loading and the memory used by the shaders
class MaterialManager : public ResourceManager
{
public:
	Resource* LoadResource(const string& name, const int type = 0);

	//singleton getter
	static MaterialManager&  getInstance()
	{
		static MaterialManager instance;
		return instance;
	}

	~MaterialManager() { UnloadAllResources(); }

private:
	//These parts enforce singleton constraints
	MaterialManager(){};
	Shader* LoadShader(string vertex, string fragment, string geometry = "", string tcs = "", string tes = "");
};
