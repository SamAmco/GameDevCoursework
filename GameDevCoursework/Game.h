//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Renderer.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "Scene1.h"
#include "MainMenuScene.h"
#include "YouLoseScene.h"
#include "YouWinScene.h"

//The game class controls the game flow,
//it holds a pointer to the current scene and determines when to load and unload scenes
class Game
{
public:
	Game(Renderer&);

	bool Update(sf::Event& event, float msec);
	void DrawGUI(sf::RenderWindow& window);

	~Game();

private:
	void loadNextScene(Scenes sceneType);

	Renderer& renderer;
	Scene* currentScene;
	Scenes currentSceneType;
};

