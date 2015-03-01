#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "btBulletDynamicsCommon.h"
#include <SFML/Window.hpp>


class Player
{
public:
	Player(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position);
	~Player();

	void Update(sf::Event& event, float msec);
	btRigidBody* sphereRigidBody;

private:
	void initializeGraphics(const Vector3& position);
	void initializePhysics(const Vector3& position);

	btCollisionShape* shpereShape;
	btDefaultMotionState* sphereMotionState;

	RenderObject* renderObject;
	Renderer& renderer;
	btDiscreteDynamicsWorld* dynamicsWorld;

	//const float
};

