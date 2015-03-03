#pragma once
#include "Scene.h"
#include "GraphicsCode\Renderer.h"
#include "btBulletDynamicsCommon.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Goal.h"
#include "SolidPlatform.h"

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
	btCollisionShape* groundShape;
	btDefaultMotionState* groundMotionState;
	btRigidBody* groundRigidBody;
	btSequentialImpulseConstraintSolver* solver;

	Player* player;
	Goal* goal;

	SolidPlatform* p1;
	SolidPlatform* p2;
};

