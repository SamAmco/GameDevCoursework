//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "MaterialManager.h"

Resource* MaterialManager::LoadResource(const string& name, const int type)
{
	//if the material is already loaded, return that
	for (auto m : loadedResources)
	{
		if (m->name.compare(name) == 0)
			return m;
	}

	//otherwise read in the material file
	using namespace std;

	//Find the right file
	FILE* file;
	stringstream s;
	s << "Materials/" << name << ".txt";
	cout << "Loading: " << s.str() << endl;
	errno_t err = fopen_s(&file, s.str().c_str(), "r");
	if (err)
	{
		cout << "Impossible to open the file " << s.str() << "\n";
		return NULL;
	}

	const int arrSize = 128;
	char lineHeader[arrSize];
	char vertex[arrSize]	= "";
	char fragment[arrSize]	= "";
	char geometry[arrSize]	= "";
	char tcs[arrSize]		= "";
	char tes[arrSize]		= "";

	//Loop through the lines
	while (1)
	{
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, arrSize);
		if (res == EOF)
			break;
		
		//given the word, read in the shader name to the correct char[]
		if (strcmp(lineHeader, "vertex") == 0)
			fscanf_s(file, "%s\n", &vertex, arrSize);
		else if (strcmp(lineHeader, "fragment") == 0)
			fscanf_s(file, "%s\n", &fragment, arrSize);
		else if (strcmp(lineHeader, "geometry") == 0)
			fscanf_s(file, "%s\n", &geometry, arrSize);
		else if (strcmp(lineHeader, "tcs") == 0)
			fscanf_s(file, "%s\n", &tcs, arrSize);
		else if (strcmp(lineHeader, "tes") == 0)
			fscanf_s(file, "%s\n", &tes, arrSize);
	}

	//Load the shader, wrap it in a material resource and return it
	MaterialResource* mat = new MaterialResource();
	mat->name = name;
	Shader* sh = LoadShader(vertex, fragment, geometry, tcs, tes);
	mat->shader = sh;
	mat->failedToLoad = sh->UsingDefaultShader();
	loadedResources.push_back(mat);
	return mat;
}

Shader* MaterialManager::LoadShader(string vertex, string fragment, string geometry, string tcs, string tes)
{
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

	return s;
}
