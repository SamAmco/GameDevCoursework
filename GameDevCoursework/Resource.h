#pragma once
#include <string>

class Resource
{
public:
	Resource(){ name = ""; }
	~Resource(){}

	bool failedToLoad = false;
	bool destroyOnSceneLoad = true;
	std::string name;
};

