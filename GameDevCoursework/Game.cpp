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
}

//Update the current scene and see whether it wants to load a different scene
bool Game::Update(sf::Event& event, float msec)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::R)
		{
			loadNextScene(Scenes::RELOAD);
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
	int levelNumber = 0;
	if (sceneType == Scenes::CHOSEN_LEVEL)
	{
		levelNumber = ((MainMenuScene*)currentScene)->levelSelected;
	}
	
	delete currentScene;

	switch (sceneType)
	{
	case Scenes::MAIN_MENU :
		currentScene = new MainMenuScene(gui);
		break;
	case Scenes::NEXT_LEVEL:
		currentScene = new Scene1(renderer, gui, true);
		break;
	case Scenes::CHOSEN_LEVEL:
		currentScene = new Scene1(renderer, gui, false);
		break;
	case Scenes::RELOAD:
		currentScene = new Scene1(renderer, gui, false);
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
