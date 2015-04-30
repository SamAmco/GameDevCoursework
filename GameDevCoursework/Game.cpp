//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Game.h"

bool Game::continueGame = true;
bool Game::gamePaused = false;

Game::Game(Renderer& renderer, tgui::Gui& gui)
	: renderer(renderer), gui(gui)
{
	//initialize the opening scene to the main menu
	currentScene = new MainMenuScene(gui);
	currentSceneType = Scenes::MAIN_MENU;
}

//Update the current scene and see whether it wants to load a different scene
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
			//return false;
		}
	}


	if (gamePaused)
		msec = 0;

	Scenes s = currentScene->Update(event, msec);

	if (s != Scenes::CURRENT)
		loadNextScene(s);

	return continueGame;
}

//Change the current scene
void Game::loadNextScene(Scenes sceneType)
{
	delete currentScene;
	currentSceneType = sceneType;
	switch (sceneType)
	{
	case Scenes::MAIN_MENU :
		currentScene = new MainMenuScene(gui);
		break;
	case Scenes::SCENE1:
		currentScene = new Scene1(renderer, gui);
		break;
	}
	gamePaused = false;
}

//Draw the gui for the current scene.
void Game::HandleUI(tgui::Gui& gui)
{
	currentScene->HandleUI();
}

Game::~Game()
{
	delete currentScene;
}
