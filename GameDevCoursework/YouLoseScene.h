//File Written by Samuel Amantea-Collins
#pragma once
#include "Scene.h"

//The scene that displays the "you lose" message when the player dies
class YouLoseScene : public Scene
{
public:
	YouLoseScene();
	~YouLoseScene();

	Scenes Update(sf::Event& event, float msec);
	void DrawGUI(sf::RenderWindow& window);

private:
	sf::Text text;
	sf::Font font;
};

