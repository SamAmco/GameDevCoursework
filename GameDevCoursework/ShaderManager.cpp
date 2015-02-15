#include "stdafx.h"
#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
	loadedShaders = map<string, Shader*>();
}

void ShaderManager::UnloadShaders()
{
	std::map<string, Shader*>::const_iterator i = loadedShaders.begin();
	while (i != loadedShaders.end())
	{
		Shader* s = i->second;
		cout << "deleting shader " << i->first << "\n";
		delete s;
		++i;
	}
	loadedShaders.clear();
}

Shader* ShaderManager::LoadShader(string vertex, string fragment, string geometry, string tcs, string tes)
{
	string index = vertex + fragment + geometry + tcs + tes;
	std::map<string, Shader*>::const_iterator i = loadedShaders.find(index);
	if (i != loadedShaders.end())
		return (*i).second;

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
}
