#pragma once
#include "Resource.h"
#include "GraphicsCode\Shader.h"

class MaterialResource : public Resource
{
public:

	MaterialResource(){}
	~MaterialResource(){ delete shader; }

	Shader* shader;
};

