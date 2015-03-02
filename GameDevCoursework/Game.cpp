#include "stdafx.h"
#include "Game.h"

Game::Game(Renderer& renderer)
	: renderer(renderer)
{
	currentScene = new Scene1(renderer);
}


bool Game::Update(sf::Event event, float msec)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::R)
		{
			delete currentScene;
			currentScene = new Scene1(renderer);
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			return false;
		}
	}
	currentScene->Update(event, msec);
	return true;
}

Game::~Game()
{
	delete currentScene;
}
