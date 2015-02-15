#pragma once
#include "GraphicsCode\Shader.h"
#include <string>
#include <map>

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
	ShaderManager();
	ShaderManager(ShaderManager const&) = delete;
	void operator=(ShaderManager const&) = delete;

	map<string, Shader*> loadedShaders;
};
