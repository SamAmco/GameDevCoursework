//File Written by Samuel Amantea-Collins
#pragma once
#include "Texture.h"
#include <string>
#include <map>

using namespace std;

//Manages Texture loading and the memory used by the textures
class TextureManager
{
public:
	Texture LoadTexture(string name);

	//singleton getter
	static TextureManager& getInstance()
	{
		static TextureManager instance;
		
		return instance;
	}

	void UnloadTextures();

	~TextureManager();
private:
	//These parts enforce singleton constraints
	TextureManager();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	//Store a map of already loaded textures
	map<string, Texture> loadedTextures;
};

