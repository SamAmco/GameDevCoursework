//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "MainMenuScene.h"

//Load the font and text and initialize the background music
MainMenuScene::MainMenuScene(tgui::Gui& gui, vector<string>& levelNames) : Scene(gui)
{
	nextScene = Scenes::CURRENT;
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(true);

	TextureManager::getInstance().LoadResource("Dunes.txt", TextureType::CUBE_MAP);

	GuiLoader::LoadMainMenuGui(gui, levelNames);
	backgroundMusic = (MusicResource*)AudioManager::getInstance().LoadResource("simple_soul_in_a_mechanical_world.wav", AUDIO_TYPE::MUSIC);
	backgroundMusic->music->setLoop(true);

	AudioManager::getInstance().PlayMusicResource(backgroundMusic);
}

Scenes MainMenuScene::Update(sf::Event& event, float msec)
{
	return nextScene;
}

//Draw the text
void MainMenuScene::HandleUI()
{
	tgui::Callback callback;
	while (gui.pollCallback(callback))
	{
		//if there is a gui event, check the id of the gui element
		if (callback.id > 0)
		{
			levelSelected = callback.id - 1;
			nextScene = Scenes::CHOSEN_LEVEL;
		}
	}
}
