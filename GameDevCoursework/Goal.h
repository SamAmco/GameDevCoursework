#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Player.h"

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
	const float WIN_THRESHOLD = 4.5f;
};

