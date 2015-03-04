#pragma once
#include "GraphicsCode\Renderer.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "Scene1.h"
#include "MainMenuScene.h"
#include "YouLoseScene.h"
#include "YouWinScene.h"


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

