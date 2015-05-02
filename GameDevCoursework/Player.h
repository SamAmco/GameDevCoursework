//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "MaterialManager.h"
#include "btBulletDynamicsCommon.h"
#include <SFML/Window.hpp>
#include "ThirdPersonCamera.h"

//A player is a ball controlled by the user that has a camera attached
class Player
{
public:
	Player(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3 position);
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
	ThirdPersonCamera camera;

	//TODO: these values are hard coded for now, consider a more data driven approach
	const float torquePower = 16.0f;
	const float jumpPower = 2.0f;

	//This is for debugging purposes, it enables you to disable the player controls so that you 
	//can regain control of your mouse by pressing return.
	bool hasControl = true;
};

