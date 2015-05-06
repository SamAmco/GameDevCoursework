//File Written by Samuel Amantea-Collins
#pragma once
#include "MeshManager.h"
#include "TextureManager.h"
#include "MaterialManager.h"
#include "AudioManager.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI\TGUI.hpp>
#include "GuiLoader.h"


//This enumerator is used to navigate scenes. CURRENT is a special value that is used to
//denote the scene that is currently loaded, MAIN_MENU simply denotes the main menu scene,
//NEXT_LEVEL denotes the level after the current one,
//where as CHOSEN_LEVEL denotes the level chosen from the main menu scene. RELOAD signifies that
//a given scene should be reloaded.
enum Scenes
{
	CURRENT,
	MAIN_MENU,
	NEXT_LEVEL,
	CHOSEN_LEVEL,
	RELOAD
};

//This abstract class is the base for all scenes and ensures that all resources are unloaded
//when a scene is destroyed
class Scene
{
public:

	Scene(tgui::Gui& gui) : gui(gui)
	{
		gui.removeAllWidgets();
	}

	virtual Scenes Update(sf::Event& event, float msec) = 0;
	virtual void HandleUI() {}

	virtual ~Scene()
	{
		MeshManager::getInstance().LoadingNewScene();
		TextureManager::getInstance().LoadingNewScene();
		MaterialManager::getInstance().LoadingNewScene();
		AudioManager::getInstance().LoadingNewScene();
	}
protected:
	tgui::Gui& gui;
	Scenes nextScene;

};

