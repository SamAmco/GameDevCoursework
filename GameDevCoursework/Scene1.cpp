//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Scene1.h"
#include "Game.h"


Scene1::Scene1(Renderer& renderer, tgui::Gui& gui, string levelName, bool lastLevel)
	: Scene(gui), lastLevel(lastLevel), renderer(renderer)
{
	solidPlatforms = vector<SolidPlatform*>();

	nextScene = Scenes::CURRENT;
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(false);

	//set up the physics engine and renderer
	initializeGraphics();
	initializePhysics();

	//Create the in game objects
	readLevelDataIn(levelName);
	
	//load the background music
	backgroundMusic = (MusicResource*)AudioManager::getInstance().LoadResource("Audio/tacky_background_music.wav", AUDIO_TYPE::MUSIC);
	backgroundMusic->music->setLoop(true);
	AudioManager::getInstance().PlayMusicResource(backgroundMusic);
}

#define MAX_READ_IN_CHARS 128

void Scene1::readLevelDataIn(string& levelName)
{
	using namespace std;

	FILE* file;
	stringstream s;
	s << "Levels/" << levelName;
	cout << "Loading: " << s.str() << endl;
	errno_t err = fopen_s(&file, s.str().c_str(), "r");
	if (err)
	{
		cout << "Impossible to open the file " << s.str() << "\n";
		return;
	}

	char lineHeader[MAX_READ_IN_CHARS];

	//Loop through the lines
	while (1)
	{
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, MAX_READ_IN_CHARS);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "GameObject:") == 0)
		{
			char name[MAX_READ_IN_CHARS] = "";
			btQuaternion rotation;
			btVector3 position;
			btVector3 scale;

			while (1)
			{
				int res2 = fscanf_s(file, "%s", lineHeader, MAX_READ_IN_CHARS);
				if (res2 == EOF)
					break;

				if (strcmp(lineHeader, "m_Name:") == 0)
				{
					fscanf_s(file, "%s\n", &name, MAX_READ_IN_CHARS);
					//cout << name << endl;
					break;
				}
			}

			readTransformIn(file, rotation, position, scale);

			if (strcmp(name, "Cube") == 0)
			{
				SolidPlatform* sp = new SolidPlatform(renderer, dynamicsWorld, position, rotation, scale / 2.f, "red.png");
				solidPlatforms.push_back(sp);
			}
			else if (strcmp(name, "PlayerStart") == 0)
				player = new Player(renderer, dynamicsWorld, position);
			else if (strcmp(name, "Goal") == 0)
				goal = new Goal(renderer, *player, Vector3(position));

		}
	}
}

void Scene1::readTransformIn(FILE* file, btQuaternion& rotation, btVector3& position, btVector3& scale)
{
	char lineHeader[MAX_READ_IN_CHARS];

	while (1)
	{
		int res2 = fscanf_s(file, "%s", lineHeader, MAX_READ_IN_CHARS);
		if (res2 == EOF)
			break;

		if (strcmp(lineHeader, "m_LocalRotation:") == 0)
		{
			float x;
			float y;
			float z;
			float w;
			fscanf_s(file, " {x: %f , y: %f , z: %f , w: %f }", &x, &y, &z, &w, MAX_READ_IN_CHARS);
			rotation.setValue(x, y, z, w);
			//cout << x << ',' << y << ',' << z << ',' << w << endl;
		}
		if (strcmp(lineHeader, "m_LocalPosition:") == 0)
		{
			float x;
			float y;
			float z;
			fscanf_s(file, " {x: %f , y: %f , z: %f }", &x, &y, &z, MAX_READ_IN_CHARS);
			position.setValue(x, y, z);
			//cout << x << ',' << y << ',' << z << endl;
		}
		if (strcmp(lineHeader, "m_LocalScale:") == 0)
		{
			float x;
			float y;
			float z;
			fscanf_s(file, " {x: %f , y: %f , z: %f }", &x, &y, &z, MAX_READ_IN_CHARS);
			scale.setValue(x, y, z);
			//cout << x << ',' << y << ',' << z << endl;
			break;
		}
	}
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
	}

	return nextScene;
}

void Scene1::HandleUI()
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

Scene1::~Scene1()
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
}
