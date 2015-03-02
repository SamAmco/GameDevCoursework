#pragma once
#include "GraphicsCode\Renderer.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "Scene1.h"


class Game
{
public:
	Game(Renderer&);

	bool Update(sf::Event event, float msec);

	~Game();

private:
	Renderer& renderer; 
	Scene* currentScene;
};

