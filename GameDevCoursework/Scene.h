#pragma once
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

class Scene
{
public:

	Scene(){}

	virtual void Update(sf::Event event, float msec) = 0;

	virtual ~Scene()
	{
		MeshManager::getInstance().UnloadMeshes();
		TextureManager::getInstance().UnloadTextures();
		ShaderManager::getInstance().UnloadShaders();
	}
};

