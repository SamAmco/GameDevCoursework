//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Game.h"

//These two public static variables are accessed by gui elements 
bool Game::continueGame = true;
bool Game::gamePaused = false;

Game::Game(Renderer& renderer, tgui::Gui& gui)
	: renderer(renderer), gui(gui)
{
	levelNames = vector<string>();

	//This code requires an external header called dirent
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("Levels\\")) != NULL) 
	{
		while ((ent = readdir(dir)) != NULL) 
		{
			string s = ent->d_name;
			if (s.find(".unity") != std::string::npos)
				levelNames.push_back(s);
		}
		closedir(dir);
	}
	else 
		cout << "Could not open levels directory!" << endl;

	currentScene = new MainMenuScene(gui, levelNames);
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

	//when the game is paused we send the special value of 0 to the scene
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
	if (sceneType == Scenes::CHOSEN_LEVEL)
		levelNumber = ((MainMenuScene*)currentScene)->levelSelected;
	else if (sceneType == Scenes::NEXT_LEVEL)
		++levelNumber;

	delete currentScene;
	
	switch (sceneType)
	{
	case Scenes::MAIN_MENU :
		currentScene = new MainMenuScene(gui, levelNames);
		break;
	case Scenes::NEXT_LEVEL:
	case Scenes::CHOSEN_LEVEL :
	case Scenes::RELOAD :
		currentScene = new LevelScene(renderer, gui, levelNames[levelNumber], levelNumber == levelNames.size() - 1);
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
