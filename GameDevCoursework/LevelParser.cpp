#include "stdafx.h"
#include "LevelParser.h"


const std::string LevelParser::LEVELS_LOCATION = "Levels/";
const int LevelParser::MAX_READ_IN_CHARS = 128;


void LevelParser::ReadLevelDataIn(string& levelName, Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld,
	vector<SolidPlatform*>& solidPlatforms, vector<MovingPlatform*>& movingPlatforms, Goal** goal, Player** player,
	string& musicName)
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


			if (strcmp(name, "SolidPlatform") == 0)
			{
				ReadTransformIn(file, rotation, position, scale);
				position.setZ(-position.z());
				SolidPlatform* sp = new SolidPlatform(renderer, dynamicsWorld, position, rotation, scale / 2.f, "red.png");
				solidPlatforms.push_back(sp);
			}
			else if (strcmp(name, "MovingPlatform") == 0)
			{
				btVector3 startPos;
				btVector3 endPos;
				float moveSpeed;
				
				ReadMovingPlatformDataIn(file, startPos, endPos, moveSpeed);
				ReadTransformIn(file, rotation, position, scale);

				position.setZ(-position.z());
				startPos.setZ(-startPos.z());
				endPos.setZ(-endPos.z());

				MovingPlatform* mp = new MovingPlatform(renderer, dynamicsWorld, position, rotation, scale / 2.f, "red.png",
					startPos, endPos, moveSpeed);
				movingPlatforms.push_back(mp);
			}
			else if (strcmp(name, "PlayerStart") == 0)
			{
				ReadTransformIn(file, rotation, position, scale);
				position.setZ(-position.z());
				*player = new Player(renderer, dynamicsWorld, position);
			}
			else if (strcmp(name, "Goal") == 0)
			{
				ReadTransformIn(file, rotation, position, scale);
				position.setZ(-position.z());
				*goal = new Goal(renderer, **player, Vector3(position));
			}
			else if (strcmp(name, "LevelData") == 0)
				ReadLevelDataIn(file, musicName);
		}
	}
}

void LevelParser::ReadLevelDataIn(FILE* file, string& musicName)
{
	char lineHeader[MAX_READ_IN_CHARS];
	string cubeMap;

	while (1)
	{
		int res2 = fscanf_s(file, "%s", lineHeader, MAX_READ_IN_CHARS);
		if (res2 == EOF)
			break;

		if (strcmp(lineHeader, "cubeMap:") == 0)
			ReadStringIn(file, cubeMap);
		else if (strcmp(lineHeader, "backgroundMusic:") == 0)
		{
			ReadStringIn(file, musicName);
			break;
		}
	}

	TextureManager::getInstance().LoadResource(cubeMap, TextureType::CUBE_MAP);
}

void LevelParser::ReadMovingPlatformDataIn(FILE* file, btVector3& startPos, btVector3& endPos, float& moveSpeed)
{
	char lineHeader[MAX_READ_IN_CHARS];

	while (1)
	{
		int res2 = fscanf_s(file, "%s", lineHeader, MAX_READ_IN_CHARS);
		if (res2 == EOF)
			break;

		if (strcmp(lineHeader, "startPos:") == 0)
			ReadVec3In(file, startPos);
		if (strcmp(lineHeader, "endPos:") == 0)
			ReadVec3In(file, endPos);
		if (strcmp(lineHeader, "moveSpeed:") == 0)
		{
			ReadFloatIn(file, moveSpeed);
			break;
		}
	}
}

void LevelParser::ReadTransformIn(FILE* file, btQuaternion& rotation, btVector3& position, btVector3& scale)
{
	char lineHeader[MAX_READ_IN_CHARS];

	while (1)
	{
		int res2 = fscanf_s(file, "%s", lineHeader, MAX_READ_IN_CHARS);
		if (res2 == EOF)
			break;

		if (strcmp(lineHeader, "m_LocalRotation:") == 0)
			ReadQuatIn(file, rotation);
		if (strcmp(lineHeader, "m_LocalPosition:") == 0)
			ReadVec3In(file, position);
		if (strcmp(lineHeader, "m_LocalScale:") == 0)
		{
			ReadVec3In(file, scale);
			break;
		}
	}
}

void LevelParser::ReadVec3In(FILE* file, btVector3& vec)
{
	float x;
	float y;
	float z;
	fscanf_s(file, " {x: %f , y: %f , z: %f , w: %f }", &x, &y, &z, MAX_READ_IN_CHARS);
	vec.setValue(x, y, z);
}

void LevelParser::ReadQuatIn(FILE* file, btQuaternion& quat)
{
	float x;
	float y;
	float z;
	float w;
	fscanf_s(file, " {x: %f , y: %f , z: %f , w: %f }", &x, &y, &z, &w, MAX_READ_IN_CHARS);
	quat.setValue(x, y, z, w);
}

void LevelParser::ReadFloatIn(FILE* file, float& f)
{
	fscanf_s(file, " %f", &f, MAX_READ_IN_CHARS);
}

void LevelParser::ReadStringIn(FILE* file, string& s)
{
	char c[MAX_READ_IN_CHARS] = "";
	fscanf_s(file, " %s", &c, MAX_READ_IN_CHARS);
	s = c;
}