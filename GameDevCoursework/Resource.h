#pragma once
#include <string>

class Resource
{
public:
	Resource(){ name = ""; }
	virtual ~Resource(){}

	bool failedToLoad = false;
	bool destroyOnSceneLoad = true;
	std::string name;
};

