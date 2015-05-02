//File Written by Samuel Amantea-Collins
#pragma once
#include "Scene.h"
#include "MusicResource.h"

//The scene for the main menu. Simply says press space to play and moves to Scene1
class MainMenuScene : public Scene
{
public:
	MainMenuScene(tgui::Gui& gui, int numberOfLevels);
	~MainMenuScene(){}

	Scenes Update(sf::Event& event, float msec);
	virtual void HandleUI();

	int levelSelected = 0;

private:
	MusicResource* backgroundMusic;
};

