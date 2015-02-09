#pragma once
#include <GL\glew.h>
#include <iostream>
#include <string>
#include "Texture.h"

using namespace std;

class ResourceManager
{
public:
	ResourceManager();

	Texture LoadTexture(string name) const;
	
	static ResourceManager& getInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	~ResourceManager();

private:
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;
};
