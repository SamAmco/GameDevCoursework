#include "stdafx.h"
#include "Scene1.h"


Scene1::Scene1(Renderer& renderer)
	: renderer(renderer)
{
	initializeGraphics();
	initializePhysics();
}

void Scene1::initializeGraphics()
{
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));
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

	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -3, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	player = new Player(renderer, dynamicsWorld, Vector3(0, 2, -10));
	//player2 = new Player(renderer, dynamicsWorld, Vector3(0, 4, -9));
}

void Scene1::Update(sf::Event event, float msec)
{
	//cout << msec << endl;
	player->Update(event, msec);
	dynamicsWorld->stepSimulation(msec);
	//cout << Vector3(player->sphereRigidBody->getAngularVelocity()) << endl;
	//player2->Update(event, msec);
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
}
