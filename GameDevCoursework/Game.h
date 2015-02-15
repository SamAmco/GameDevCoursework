#pragma once
#include "GraphicsCode\Renderer.h"

class Game
{
public:
	Game(Renderer&);

	void Update(sf::Event event, float msec);

	~Game();
private:
	Renderer& renderer;

	vector<Shader*> shaders;
	int shaderInd;
	RenderObject o;
	Vector3 lightCol;
	Vector3 lightPos;
	float lightRad;
};

