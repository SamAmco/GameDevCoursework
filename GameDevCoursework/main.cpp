#include "stdafx.h"
#include <GL\glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include "GraphicsCode\Renderer.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "Game.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// create the window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	sf::Window window = sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	Renderer renderer = Renderer();
	window.setVerticalSyncEnabled(true);

	if (glewInit() != GLEW_OK) 
	{	//Try to initialise GLEW
		std::cout << "OGLRenderer::OGLRenderer(): Cannot initialise GLEW!" << std::endl;
		return -1;
	}

	Game game = Game(renderer);

	bool running = true;
	sf::Clock clock;
	while (running)
	{
		float msec = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			else if (event.type == sf::Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);
		}
		else
			event = sf::Event();

		game.Update(event, msec);//physics update
		
		renderer.UpdateScene(msec);//graphics update

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear the screen

		renderer.RenderScene();//Draw the scene to the buffer

		window.display();//Display the buffer
	}

	TextureManager::getInstance().UnloadTextures();
	MeshManager::getInstance().UnloadMeshes();
	ShaderManager::getInstance().UnloadShaders();

	return 0;
}
