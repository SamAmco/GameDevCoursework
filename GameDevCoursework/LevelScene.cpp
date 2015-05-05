//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "LevelScene.h"
#include "Game.h"


LevelScene::LevelScene(Renderer& renderer, tgui::Gui& gui, string levelName, bool lastLevel)
	: Scene(gui), lastLevel(lastLevel), renderer(renderer)
{
	solidPlatforms = vector<SolidPlatform*>();
	movingPlatforms = vector<MovingPlatform*>();

	nextScene = Scenes::CURRENT;
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(false);

	//set up the physics engine and renderer
	initializeGraphics();
	initializePhysics();

	//Create the in game objects
	LevelParser::ReadLevelDataIn(levelName, renderer, dynamicsWorld, solidPlatforms, movingPlatforms, &goal, &player);
	
	//load the background music
	backgroundMusic = (MusicResource*)AudioManager::getInstance().LoadResource("tacky_background_music.wav", AUDIO_TYPE::MUSIC);
	backgroundMusic->music->setLoop(true);
	AudioManager::getInstance().PlayMusicResource(backgroundMusic);
}

//Simply sets the light position and projection matrix of the scene
void LevelScene::initializeGraphics()
{
	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(20.0f, 20.0f, -10);
	float lightRad = 3000.0f;

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
}

//create the physics engine and what ever else it requires.
void LevelScene::initializePhysics()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

//if the player has fallen below the platforms, or the goal has been reached, return a change of scene
Scenes LevelScene::Update(sf::Event& event, float msec)
{
	if (msec > 0)
	{
		player->Update(event, msec);
		dynamicsWorld->stepSimulation(msec);
	
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				GuiLoader::LoadSettingsOverlay2(gui);
			}
		}

		if (player->sphereRigidBody->getWorldTransform().getOrigin().y() < -5)
			GuiLoader::LoadLevelLostOverlay(gui);

		if (goal->Update(event, msec))
		{
			if (lastLevel)
				GuiLoader::LoadGameWonOverlay(gui);
			else
				GuiLoader::LoadLevelWonOverlay(gui);
		}

		for (auto p : movingPlatforms)
			p->Update(event, msec);
	}

	return nextScene;
}

void LevelScene::HandleUI()
{
	tgui::Callback callback;
	while (gui.pollCallback(callback))
	{
		//if there is a gui event, check the id of the gui element
		if (callback.id == 1)
		{
			nextScene = Scenes::MAIN_MENU;
		}
		else if (callback.id == 2)
		{
			nextScene = Scenes::NEXT_LEVEL;
		}
		else if (callback.id == 3)
		{
			nextScene = Scenes::RELOAD;
		}
	}
}

LevelScene::~LevelScene()
{
	delete dynamicsWorld;
	delete broadphase;
	delete collisionConfiguration;
	delete dispatcher;
	delete solver;
	delete player;
	delete goal;
	for (auto p : solidPlatforms)
		delete p;
	for (auto p : movingPlatforms)
		delete p;
}
