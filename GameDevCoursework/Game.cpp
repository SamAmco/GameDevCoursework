//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Game.h"

bool Game::continueGame = true;
bool Game::gamePaused = false;

Game::Game(Renderer& renderer, tgui::Gui& gui)
	: renderer(renderer), gui(gui)
{
	//initialize the opening scene to the main menu
	levelNames = vector<string>();

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("Levels\\")) != NULL) 
	{
		/* print all the files and directories within directory */
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

	currentScene = new MainMenuScene(gui, levelNames.size());
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
	if (sceneType == Scenes::CHOSEN_LEVEL)
		levelNumber = ((MainMenuScene*)currentScene)->levelSelected;
	else if (sceneType == Scenes::NEXT_LEVEL)
		++levelNumber;

	delete currentScene;
	
	switch (sceneType)
	{
	case Scenes::MAIN_MENU :
		currentScene = new MainMenuScene(gui, levelNames.size());
		break;
	case Scenes::NEXT_LEVEL:
	case Scenes::CHOSEN_LEVEL :
	case Scenes::RELOAD :
		currentScene = new Scene1(renderer, gui, levelNames[levelNumber], levelNumber == levelNames.size() - 1);
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
