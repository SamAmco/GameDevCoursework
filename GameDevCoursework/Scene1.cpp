//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Scene1.h"


Scene1::Scene1(Renderer& renderer)
	: renderer(renderer)
{
	//set up the physics engine and renderer
	initializeGraphics();
	initializePhysics();

	//Create the in game objects
	player = new Player(renderer, dynamicsWorld, Vector3(0, 2, -5));
	p1 = new SolidPlatform(renderer, dynamicsWorld, Vector3(0,0,0), Vector3(10, 1, 10), "red.png");
	p2 = new SolidPlatform(renderer, dynamicsWorld, Vector3(0,0,-35), Vector3(10, 1, 10), "red.png");
	goal = new Goal(renderer, *player, Vector3(0, 0, -40));
	
	//load the background music
	backgroundMusic = (MusicResource*)AudioManager::getInstance().LoadResource("Audio/tacky_background_music.wav", AUDIO_TYPE::MUSIC);
	backgroundMusic->music->setLoop(true);
	backgroundMusic->music->play();
}

//Simply sets the light position and projection matrix of the scene
void Scene1::initializeGraphics()
{
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
}

//create the physics engine and what ever else it requires.
void Scene1::initializePhysics()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

//if the player has fallen below the platforms, or the goal has been reached, return a change of scene
Scenes Scene1::Update(sf::Event& event, float msec)
{
	player->Update(event, msec);
	dynamicsWorld->stepSimulation(msec);

	if (player->sphereRigidBody->getWorldTransform().getOrigin().y() < -5)
		return Scenes::YOU_LOSE_SCENE;

	if (goal->Update(event, msec))
		return Scenes::YOU_WIN_SCENE;

	return Scenes::CURRENT;
}

Scene1::~Scene1()
{
	delete dynamicsWorld;
	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete player;
	delete p1;
	delete p2;
	delete goal;
}
