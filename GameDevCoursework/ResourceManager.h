//File Written by Samuel Amantea-Collins
#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "Resource.h"

using namespace std;

//This is the abstract class for all resource managers, it allows all resource managers
//to store their resources and destroy them in the same way.
class ResourceManager
{
public:

	virtual Resource* LoadResource(const std::string& name, const int type = 0) = 0;
	virtual void UnloadAllResources();
	virtual void LoadingNewScene();

	~ResourceManager(){}

protected:
	//These parts enforce singleton constraints
	ResourceManager();
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;

	vector<Resource*> loadedResources;
};

