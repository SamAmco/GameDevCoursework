#include "stdafx.h"
#include "Scene1.h"


Scene1::Scene1(Renderer& renderer)
	: renderer(renderer)
{
	initializeGraphics();
	initializePhysics();
	player = new Player(renderer, dynamicsWorld, Vector3(0, 2, -5));
	goal = new Goal(renderer, *player, Vector3(0, 0, 40));
	p1 = new SolidPlatform(renderer, dynamicsWorld, Vector3(0,0,0), Vector3(10, 1, 10), "red.png");
	p2 = new SolidPlatform(renderer, dynamicsWorld, Vector3(0,0,35), Vector3(10, 1, 10), "red.png");
}

void Scene1::initializeGraphics()
{
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
}

void Scene1::initializePhysics()
{
	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -100, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);
}

void Scene1::Update(sf::Event event, float msec)
{
	player->Update(event, msec);
	goal->Update(event, msec);
	dynamicsWorld->stepSimulation(msec);
}

Scene1::~Scene1()
{
	delete dynamicsWorld;
	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete groundShape;
	delete groundMotionState;
	delete groundRigidBody;
	delete solver;
	delete player;
	delete p1;
	delete p2;
	delete goal;
}
