#include "stdafx.h"
#include "TextureManager.h"
#include <SOIL.h>
#include <iostream>


TextureManager::TextureManager()
{
	loadedTextures = map<string, Texture>();
}

Texture TextureManager::LoadTexture(string name)
{
	std::map<string, Texture>::const_iterator i = loadedTextures.find(name);
	if (i != loadedTextures.end())
		return (*i).second;

	GLuint t = SOIL_load_OGL_texture(name.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	Texture texture = Texture();
	if (!t)
		cout << "GLuint Renderer::LoadTexture(string name) FAILED TO LOAD " << name << endl;
	else
		texture = Texture(name, t);

	loadedTextures.insert(std::pair<string, Texture>(name, texture));

	return texture;
}

TextureManager::~TextureManager()
{
}
