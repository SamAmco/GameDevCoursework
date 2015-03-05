//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
	loadedShaders = map<string, Shader*>();
}

//delete all the Shader objects from the heap and clear the map
void ShaderManager::UnloadShaders()
{
	std::map<string, Shader*>::const_iterator i = loadedShaders.begin();
	while (i != loadedShaders.end())
	{
		cout << "deleting shader " << i->first << "\n";
		delete i->second;
		++i;
	}
	loadedShaders.clear();
}

Shader* ShaderManager::LoadShader(string vertex, string fragment, string geometry, string tcs, string tes)
{
	//I use the concatenation of the shader names as the index, so any combination of different shaders will
	//return a different Shader object. 

	//if we have already loaded the Shader object, then return that
	string index = vertex + fragment + geometry + tcs + tes;
	std::map<string, Shader*>::const_iterator i = loadedShaders.find(index);
	if (i != loadedShaders.end())
		return (*i).second;

	//otherwise attempt to load it
	if (geometry != "")
		geometry = "Shaders/" + geometry + ".glsl";
	if (tcs != "")
		tcs = "Shaders/" + tcs + ".glsl";
	if (tes != "")
		tes = "Shaders/" + tes + ".glsl";

	Shader* s = new Shader("Shaders/" + vertex + ".glsl",
		"Shaders/" + fragment + ".glsl",
		geometry,
		tcs,
		tes);

	loadedShaders.insert(std::pair<string, Shader*>(index, s));
	return s;
}


ShaderManager::~ShaderManager()
{
	//Just in case
	UnloadShaders();
}
