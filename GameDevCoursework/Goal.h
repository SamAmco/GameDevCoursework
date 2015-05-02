//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "MaterialManager.h"
#include "Player.h"

//A goal is an aura of light in the game world that the player must reach 
//to win the level
class Goal
{
public:
	Goal(Renderer& renderer, Player& player, Vector3& position);
	~Goal();

	bool Update(sf::Event& event, float msec);

private:
	void initializeGraphics(const Vector3& position);

	RenderObject* renderObject;
	Player& player;
	Renderer& renderer;

	btVector3 position;
	//The distance that the player must be from the goal to win
	const float WIN_THRESHOLD = 1.5f;
};

