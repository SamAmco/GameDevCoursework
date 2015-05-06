//File Written by Samuel Amantea-Collins
#pragma once
#include <GL/glew.h>
#include <string>
#include "Resource.h"


//Stores and destroys a GLuint that refers to a texture in graphics memory
class TextureResource : public Resource
{
public:
	TextureResource() {}
	~TextureResource() 
	{
		if (!failedToLoad)
			glDeleteTextures(1, &tex);
	}
	GLuint tex;
};

