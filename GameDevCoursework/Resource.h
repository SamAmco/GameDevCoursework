//File Written by Samuel Amantea-Collins
#pragma once
#include <string>

//This is the abstract version of all resources
//it allows all resources to be managed in the same
//way
class Resource
{
public:
	Resource(){ name = ""; }
	virtual ~Resource(){}

	bool failedToLoad = false;
	bool destroyOnSceneLoad = true;
	std::string name;
};

