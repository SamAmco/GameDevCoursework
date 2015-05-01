//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Renderer.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <TGUI\TGUI.hpp>
#include "Scene1.h"
#include "MainMenuScene.h"

//The game class controls the game flow,
//it holds a pointer to the current scene and determines when to load and unload scenes
class Game
{
public:
	Game(Renderer&, tgui::Gui&);

	bool Update(sf::Event& event, float msec);
	void HandleUI(tgui::Gui& gui);
	void loadNextScene(Scenes sceneType);

	static bool continueGame;
	static bool gamePaused;

	~Game();

private:

	Renderer& renderer;
	Scene* currentScene;
	tgui::Gui& gui;
};

