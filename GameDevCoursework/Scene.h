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

//This enumerator must be updated to include the names of any 
//and all scenes in the game. CURRENT is a special value that is used to
//denote the scene that is currently loaded
enum Scenes
{
	CURRENT,
	MAIN_MENU,
	SCENE1
};

//This abstract class is the base for all scenes and ensures that all resources are unloaded
//when a scene is destroyed
class Scene
{
public:

	Scene(tgui::Gui& gui) 
	{
		gui.removeAllWidgets();
	}

	virtual Scenes Update(sf::Event& event, float msec) = 0;
	virtual void HandleUI(tgui::Gui& gui) {}

	virtual ~Scene()
	{
		MeshManager::getInstance().LoadingNewScene();
		TextureManager::getInstance().LoadingNewScene();
		MaterialManager::getInstance().LoadingNewScene();
		AudioManager::getInstance().LoadingNewScene();
	}
};

