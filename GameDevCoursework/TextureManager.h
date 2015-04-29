//File Written by Samuel Amantea-Collins
#pragma once
#include <string>
#include <vector>
#include <SOIL.h>
#include <iostream>
#include "ResourceManager.h"
#include "TextureResource.h"

using namespace std;

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
	//These parts enforce singleton constraints
	TextureManager(){};
};

