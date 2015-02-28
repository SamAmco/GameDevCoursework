#include "stdafx.h"
#include "Game.h"

Game::Game(Renderer& renderer)
	: renderer(renderer)
{
	currentScene = new Scene1(renderer);
}


void Game::Update(sf::Event event, float msec)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
	{
		delete currentScene;
		currentScene = new Scene1(renderer);
	}
	currentScene->Update(event, msec);
}

Game::~Game()
{
	delete currentScene;
}
