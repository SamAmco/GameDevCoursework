//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "TextureManager.h"


Resource* TextureManager::LoadResource(const string& name, int type)
{
	//if we have already loaded the Texture object, then return that
	for (auto t : loadedResources)
	{
		if (t->name.compare(name) == 0)
			return t;
	}
	//otherwise load the correct type of resource
	switch (type)
	{
	case TextureType::CUBE_MAP:
		return LoadCubeMap(name);
	default:
		return LoadTexture(name);
		break;
	}
}

TextureResource* TextureManager::LoadTexture(const string& name)
{
	cout << "Loading: " << name << endl;
	
	stringstream s;
	s << "Textures/" << name;

	GLuint t = SOIL_load_OGL_texture(s.str().c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	TextureResource* texture = new TextureResource();
	if (!t)
	{
		cout << "GLuint Renderer::LoadTexture(string name) FAILED TO LOAD " << s.str() << endl;
		texture->failedToLoad = true;
	}
	else
		texture->tex = t;

	texture->name = name;
	loadedResources.push_back(texture);

	return texture;
}

CubeMapResource* TextureManager::LoadCubeMap(const string& name)
{
	cout << "Loading: " << name << endl;

	//Find the file
	FILE* file;
	stringstream s;
	s << "CubeMaps/" << name;
	errno_t err = fopen_s(&file, s.str().c_str(), "r");
	if (err)
	{
		cout << "Impossible to open the file " << s.str() << "\n";
		return NULL;
	}

	const int arrSize = 128;
	char lineHeader[arrSize];
	char top[arrSize] = "";
	char bottom[arrSize] = "";
	char left[arrSize] = "";
	char right[arrSize] = "";
	char front[arrSize] = "";
	char back[arrSize] = "";

	//Loop through the lines
	while (1)
	{
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, arrSize);
		if (res == EOF)
			break;

		//given the word, read in the texture name to the correct char[]
		if (strcmp(lineHeader, "top") == 0)
			fscanf_s(file, "%s\n", &top, arrSize);
		else if (strcmp(lineHeader, "bottom") == 0)
			fscanf_s(file, "%s\n", &bottom, arrSize);
		else if (strcmp(lineHeader, "left") == 0)
			fscanf_s(file, "%s\n", &left, arrSize);
		else if (strcmp(lineHeader, "right") == 0)
			fscanf_s(file, "%s\n", &right, arrSize);
		else if (strcmp(lineHeader, "front") == 0)
			fscanf_s(file, "%s\n", &front, arrSize);
		else if (strcmp(lineHeader, "back") == 0)
			fscanf_s(file, "%s\n", &back, arrSize);
	}

	//Load the cubemap, wrap it in a cubemap resource and return it
	GLuint c = SOIL_load_OGL_cubemap(
		left, right, top, bottom, back, front,
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	CubeMapResource* cubeMap = new CubeMapResource();
	if (!c)
	{
		cout << "GLuint Renderer::LoadCubeMap(string name) FAILED TO LOAD " << name << endl;
		cubeMap->failedToLoad = true;
	}
	else
		cubeMap->cubeMap = c;

	cubeMap->name = name;
	loadedResources.push_back(cubeMap);

	return cubeMap;
}