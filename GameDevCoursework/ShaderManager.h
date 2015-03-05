//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Shader.h"
#include <string>
#include <map>

//Manages Shader loading and the memory used by the shaders
class ShaderManager
{
public:
	//singleton getter
	static ShaderManager&  getInstance()
	{
		static ShaderManager instance;
		return instance;
	}

	Shader* LoadShader(string vertex, string fragment, string geometry = "", string tcs = "", string tes = "");

	void UnloadShaders();

	~ShaderManager();

private:
	//These parts enforce singleton constraints
	ShaderManager();
	ShaderManager(ShaderManager const&) = delete;
	void operator=(ShaderManager const&) = delete;

	//Store a map of already loaded shaders
	map<string, Shader*> loadedShaders;
};
