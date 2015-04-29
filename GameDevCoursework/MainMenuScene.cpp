//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "MainMenuScene.h"

//Load the font and text and initialize the background music
MainMenuScene::MainMenuScene()
{
	font = sf::Font();
	font.loadFromFile("Fonts/OpenSans-Regular.ttf");
	text = sf::Text();
	text.setFont(font);
	text.setPosition(0, (sf::VideoMode::getDesktopMode().height / 2) - 50);
	text.setCharacterSize(44); //in pixels, not points!
	text.setColor(sf::Color(30,30,30,255));
	text.setString("Press SPACE to play the demo level");

	backgroundMusic = (MusicResource*)AudioManager::getInstance().LoadResource("Audio/simple_soul_in_a_mechanical_world.wav", AUDIO_TYPE::MUSIC);
	backgroundMusic->music->setLoop(true);
	//backgroundMusic->music->play();
}

//when the player presses space, change to Scene1
Scenes MainMenuScene::Update(sf::Event& event, float msec)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		return Scenes::SCENE1;

	return Scenes::CURRENT;
}

//Draw the text
void MainMenuScene::DrawGUI(sf::RenderWindow& window)
{
	window.draw(text);
}

MainMenuScene::~MainMenuScene()
{

}
