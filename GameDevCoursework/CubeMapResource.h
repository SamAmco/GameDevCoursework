//File Written by Samuel Amantea-Collins
#pragma once
#include <GL/glew.h>
#include "Resource.h"

//Stores a loaded cube map
class CubeMapResource : public Resource
{
public:
	CubeMapResource(){}
	virtual ~CubeMapResource()
	{
		if (!failedToLoad)
			glDeleteTextures(6, &cubeMap);
	}

	GLuint cubeMap;
};

