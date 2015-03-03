#pragma once
#include "Scene.h"

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
};

