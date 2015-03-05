//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "YouLoseScene.h"

//Load the font and set up the text
YouLoseScene::YouLoseScene()
{
	font.loadFromFile("Fonts/OpenSans-Regular.ttf");
	text = sf::Text();
	text.setFont(font);
	text.setPosition(0, (sf::VideoMode::getDesktopMode().height / 2) - 50);
	text.setCharacterSize(44); //in pixels, not points!
	text.setColor(sf::Color(30, 30, 30, 255));
	text.setString("You died :( press SPACE \nto return to the main menu");
}

//Check if the player pressed space and if so, move back to the main menu scene
Scenes YouLoseScene::Update(sf::Event& event, float msec)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		return Scenes::MAIN_MENU;

	return Scenes::CURRENT;
}

//draw the text
void YouLoseScene::DrawGUI(sf::RenderWindow& window)
{
	window.draw(text);
}

YouLoseScene::~YouLoseScene()
{
}
