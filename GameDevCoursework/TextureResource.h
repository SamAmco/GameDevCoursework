//File Written by Samuel Amantea-Collins
#pragma once
#include <GL/glew.h>
#include <string>
#include "Resource.h"


//This stores the name of a texture associated with it's position in graphics memory.
//This class should only be created by the TextureManager. Has loaded is helpful if the
//TextureManager has not been able to find the texture, because it still returns a pointer
//to a Texture object.
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

