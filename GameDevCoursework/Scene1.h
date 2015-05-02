//File Written by Samuel Amantea-Collins
#pragma once
#include "Scene.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "GraphicsCode\Renderer.h"
#include "btBulletDynamicsCommon.h"
#include "Player.h"
#include "Goal.h"
#include "SolidPlatform.h"
#include "MusicResource.h"


//This is the first level of the game. It stores the physics world for the whole game,
//the player, goal and platforms in the level.
class Scene1 : public Scene
{
public:
	Scene1(Renderer& renderer, tgui::Gui& gui, string levelName, bool lastLevel);
	virtual ~Scene1();

	virtual Scenes Update(sf::Event& event, float msec);
	virtual void HandleUI();


private:
	void initializeGraphics();
	void initializePhysics();
	void readLevelDataIn(string& levelName);
	void readTransformIn(FILE* file, btQuaternion& rotation, btVector3& position, btVector3& scale);

	Renderer& renderer;	

	btDiscreteDynamicsWorld* dynamicsWorld;
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;

	//These are visible objects in the game world
	Player* player;
	Goal* goal;
	vector<SolidPlatform*> solidPlatforms;

	MusicResource* backgroundMusic;

	bool lastLevel;
};

