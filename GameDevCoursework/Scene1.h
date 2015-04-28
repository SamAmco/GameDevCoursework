//File Written by Samuel Amantea-Collins
#pragma once
#include "Scene.h"
#include "GraphicsCode\Renderer.h"
#include "btBulletDynamicsCommon.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Goal.h"
#include "SolidPlatform.h"
#include "MusicResource.h"

//This is the first level of the game. It stores the physics world for the whole game,
//the player, goal and platforms in the level.
class Scene1 : public Scene
{
public:
	Scene1(Renderer&);
	virtual ~Scene1();

	virtual Scenes Update(sf::Event& event, float msec);

private:
	void initializeGraphics();
	void initializePhysics();

	Renderer& renderer;	

	btDiscreteDynamicsWorld* dynamicsWorld;
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;

	//These are visible objects in the game world
	Player* player;
	Goal* goal;
	SolidPlatform* p1;
	SolidPlatform* p2;

	MusicResource* backgroundMusic;
};

