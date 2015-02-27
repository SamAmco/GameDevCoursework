#pragma once
#include "GraphicsCode\Renderer.h"
#include "btBulletDynamicsCommon.h"


class Game
{
public:
	Game(Renderer&);

	void Update(sf::Event event, float msec);

	~Game();

private:	
	void initializeGraphics();
	void initializePhysics();

	Renderer& renderer;

	btDiscreteDynamicsWorld* dynamicsWorld;
	btRigidBody* sphereRigidBody;

	vector<Shader*> shaders;
	int shaderInd;
	RenderObject o;
	Vector3 lightCol;
	Vector3 lightPos;
	float lightRad;
};

