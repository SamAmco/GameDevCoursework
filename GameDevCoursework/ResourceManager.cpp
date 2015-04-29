//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	loadedResources = vector<Resource*>();
}

void ResourceManager::LoadingNewScene()
{
	auto iter = loadedResources.begin();
	//delete loaded sounds
	while (iter != loadedResources.end())
	{
		if ((*iter)->destroyOnSceneLoad)
		{
			cout << "deleting " << (*iter)->name << endl;
			delete *iter;
			iter = loadedResources.erase(iter);
		}
		else ++iter;
	}
}

//delete all the Texture objects from the heap and clear the map
void ResourceManager::UnloadAllResources()
{
	for (auto r : loadedResources)
	{
		cout << "deleting " << r->name << endl;
		delete r;
	}
	loadedResources.clear();
}