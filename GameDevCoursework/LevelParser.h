//For getting a level name without the file e
#pragma once
#include <vector>
#include "SolidPlatform.h"
#include "MovingPlatform.h"
#include "Goal.h"
#include "Player.h"

//This class holds all the functionality for reading in ".unity" level files
//and translating the data into game objects in the world
class LevelParser
{
public:

	static void ReadLevelDataIn(string& levelName, Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld,
		vector<SolidPlatform*>& solidPlatforms, vector<MovingPlatform*>& movingPlatforms, Goal** goal, Player** player,
		string& musicName);

private:
	static const std::string LEVELS_LOCATION;
	static const int MAX_READ_IN_CHARS;

	static void ReadTransformIn(FILE* file, btQuaternion& rotation, btVector3& position, btVector3& scale);
	static void ReadMovingPlatformDataIn(FILE* file, btVector3& startPos, btVector3& endPos, float& moveSpeed);
	//Level data consists of a cube map name and a background music name for the level
	static void ReadLevelDataIn(FILE* file, string& musicName);

	static void ReadVec3In(FILE* file, btVector3& vec);
	static void ReadQuatIn(FILE* file, btQuaternion& quat);
	static void ReadFloatIn(FILE* file, float& f);
	static void ReadStringIn(FILE* file, string& s);

	LevelParser(){}
	~LevelParser(){}
};

