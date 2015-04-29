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
	cout << "Loading: " << name << endl;
	//otherwise attempt to load it
	GLuint t = SOIL_load_OGL_texture(name.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	TextureResource* texture = new TextureResource();
	if (!t)
	{
		cout << "GLuint Renderer::LoadTexture(string name) FAILED TO LOAD " << name << endl;
		texture->failedToLoad = true;
		texture->name = "FAILED TO LOAD";
	}
	else
	{
		texture->name = name;
		texture->tex = t;
	}

	loadedResources.push_back(texture);

	return texture;
}