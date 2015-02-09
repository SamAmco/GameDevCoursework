#include "stdafx.h"
#include "ResourceManager.h"
#include <iostream>
#include <string>
#include <SOIL.h>

using namespace std;

ResourceManager::ResourceManager()
{
}

Texture ResourceManager::LoadTexture(string name) const
{
	GLuint t = SOIL_load_OGL_texture(name.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (!t)
	{
		cout << "GLuint Renderer::LoadTexture(string name) FAILED TO LOAD " << name << endl;
		return NULL;
	}

	Texture texture = Texture(t);

	return texture;
}

ResourceManager::~ResourceManager()
{
}
