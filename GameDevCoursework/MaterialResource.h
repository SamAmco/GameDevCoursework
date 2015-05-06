//File Written by Samuel Amantea-Collins
#pragma once
#include "Resource.h"
#include "GraphicsCode\Shader.h"

//Once a material has been read in, it can be stored simply as a shader
class MaterialResource : public Resource
{
public:

	MaterialResource(){}
	~MaterialResource(){ delete shader; }

	Shader* shader;
};

