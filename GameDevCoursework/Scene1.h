#pragma once
#include "Scene.h"
#include "GraphicsCode\Renderer.h"
#include "btBulletDynamicsCommon.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "GoalBlock.h"
#include "SolidPlatform.h"

class Scene1 : public Scene
{
public:
	Scene1(Renderer&);
	virtual ~Scene1();

	virtual void Update(sf::Event event, float msec);

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
	GoalBlock* goalBlock;

	SolidPlatform* p1;
	SolidPlatform* p2;
};

