#pragma once
#include <GL/glew.h>
#include "Resource.h"


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

