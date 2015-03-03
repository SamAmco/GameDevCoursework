#include "stdafx.h"
#include "MainMenuScene.h"


MainMenuScene::MainMenuScene()
{
	font.loadFromFile("Fonts/OpenSans-Regular.ttf");
	text = sf::Text();
	text.setFont(font);
	text.setPosition(0, (sf::VideoMode::getDesktopMode().height / 2) - 50);
	text.setCharacterSize(44); //in pixels, not points!
	text.setColor(sf::Color(30,30,30,255));
	text.setString("Press SPACE to play the demo level");
}

Scenes MainMenuScene::Update(sf::Event& event, float msec)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		return Scenes::SCENE1;

	return Scenes::CURRENT;
}

void MainMenuScene::DrawGUI(sf::RenderWindow& window)
{
	window.draw(text);
}

MainMenuScene::~MainMenuScene()
{

}
