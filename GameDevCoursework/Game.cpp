#include "stdafx.h"
#include "Game.h"

Game::Game(Renderer& renderer)
	: renderer(renderer)
{
	currentScene = new MainMenuScene();
	currentSceneType = Scenes::MAIN_MENU;
}

bool Game::Update(sf::Event& event, float msec)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::R)
		{
			loadNextScene(currentSceneType);
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			return false;
		}
	}

	Scenes s = currentScene->Update(event, msec);
	if (s != Scenes::CURRENT)
		loadNextScene(s);

	return true;
}

void Game::loadNextScene(Scenes sceneType)
{
	delete currentScene;
	currentSceneType = sceneType;
	switch (sceneType)
	{
	case Scenes::MAIN_MENU :
		currentScene = new MainMenuScene();
		break;
	case Scenes::SCENE1:
		currentScene = new Scene1(renderer);
		break;
	case Scenes::YOU_LOSE_SCENE:
		currentScene = new YouLoseScene();
		break;
	case Scenes::YOU_WIN_SCENE:
		currentScene = new YouWinScene();
		break;
	}
}

void Game::DrawGUI(sf::RenderWindow& window)
{
	currentScene->DrawGUI(window);
}

Game::~Game()
{
	delete currentScene;
}
