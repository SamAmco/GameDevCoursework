//File Written by Samuel Amantea-Collins
#pragma once
#include "Scene.h"

//The scene that displays the "you win" message when the player reaches the goal
class YouWinScene : public Scene
{
public:
	YouWinScene();
	~YouWinScene();

	Scenes Update(sf::Event& event, float msec);
	void DrawGUI(sf::RenderWindow& window);

private:
	sf::Text text;
	sf::Font font;
};

