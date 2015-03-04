//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include <GL\glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	if (glewInit() != GLEW_OK)
	{	//Try to initialise GLEW
		std::cout << "OGLRenderer::OGLRenderer(): Cannot initialise GLEW!" << std::endl;
		return -1;
	}
	
	Renderer renderer = Renderer();
	Game game = Game(renderer);

	sf::Font font;
	if (!font.loadFromFile("Fonts/OpenSans-Regular.ttf"))
		return EXIT_FAILURE;
	sf::Text text;
	text.setFont(font);
	text.setPosition(0, 0);
	text.setCharacterSize(24); // in pixels, not points!
	text.setColor(sf::Color::Red);
	window.setActive();


	bool running = true;
	sf::Clock clock;
	float totalMsec = 0;
	float iterations = 0;
	while (running)
	{
		float msec = clock.getElapsedTime().asMilliseconds();
		totalMsec += msec;
		++iterations;
		clock.restart();

		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
				break;
			}
			else if (event.type == sf::Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);
		}
		else
			event = sf::Event();

		running = game.Update(event, msec);//physics update
		
		renderer.UpdateScene(msec);//graphics update

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear the screen

		renderer.RenderScene();//Draw the scene to the buffer

		if (totalMsec >= 1000)
		{
			char temp[256];
			sprintf_s(temp, "%f", (iterations / totalMsec) * 1000.f);
			text.setString(temp);
			totalMsec = 0;
			iterations = 0;
		}
		window.pushGLStates();
		window.draw(text);
		game.DrawGUI(window);
		window.popGLStates();

		window.display();//Display the buffer
	}
	return EXIT_SUCCESS;
}
