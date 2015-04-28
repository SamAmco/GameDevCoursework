#pragma once
#include <string>
#include "Resource.h"

class ResourceManager
{
public:

	virtual Resource* LoadResource(const std::string& name, const int type = 0) = 0;
	virtual void UnloadAllResources() = 0;
	virtual void LoadingNewScene() = 0;

	~ResourceManager(){ UnloadAllResources(); }

protected:
	//These parts enforce singleton constraints
	ResourceManager(){};
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;
};

