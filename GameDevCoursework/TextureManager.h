//File Written by Samuel Amantea-Collins
#pragma once
#include <string>
#include <vector>
#include <SOIL.h>
#include <iostream>
#include "ResourceManager.h"
#include "TextureResource.h"
#include "CubeMapResource.h"

using namespace std;

//This resource manager can be used to load textures or cube maps
enum TextureType
{
	TEXTURE,
	CUBE_MAP
};

//Manages Texture loading and the memory used by the textures
class TextureManager : public ResourceManager
{
public:
	Resource* LoadResource(const string& name, const int type = 0);

	//singleton getter
	static TextureManager& getInstance()
	{
		static TextureManager instance;
		return instance;
	}

	~TextureManager(){ UnloadAllResources(); }
private:

	TextureResource* LoadTexture(const string& name);
	CubeMapResource* LoadCubeMap(const string& name);

	//These parts enforce singleton constraints
	TextureManager(){};
};

