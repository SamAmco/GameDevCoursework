#pragma once
#include "Texture.h"
#include <string>
#include <map>

using namespace std;

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

	map<string, Texture> loadedTextures;
};

