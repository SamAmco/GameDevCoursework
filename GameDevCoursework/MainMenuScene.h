//File Written by Samuel Amantea-Collins
#pragma once
#include "Scene.h"

//The scene for the main menu. Simply says press space to play and moves to Scene1
class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	~MainMenuScene();

	Scenes Update(sf::Event& event, float msec);
	void DrawGUI(sf::RenderWindow& window);

private:
	sf::Text text;
	sf::Font font;
	sf::Music* backgroundMusic;
};

