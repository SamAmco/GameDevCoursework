#pragma once
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum Scenes
{
	CURRENT,
	MAIN_MENU,
	SCENE1,
	YOU_LOSE_SCENE,
	YOU_WIN_SCENE
};

class Scene
{
public:

	Scene(){}

	virtual Scenes Update(sf::Event& event, float msec) = 0;
	virtual void DrawGUI(sf::RenderWindow& window) {}

	virtual ~Scene()
	{
		MeshManager::getInstance().UnloadMeshes();
		TextureManager::getInstance().UnloadTextures();
		ShaderManager::getInstance().UnloadShaders();
	}
};

