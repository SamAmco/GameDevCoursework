#pragma once
#include "SolidPlatform.h"

class MovingPlatform : SolidPlatform
{
public:
	MovingPlatform(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld,
		btVector3& position, btQuaternion& rotation, btVector3& boxHalfExtents, const string& texName,
		btVector3& startPos, btVector3& endPos, float moveSpeed)
		: SolidPlatform(renderer, dynamicsWorld, position, rotation, boxHalfExtents, texName),
		startPos(startPos), endPos(endPos), moveSpeed(moveSpeed), currentTargetPos(startPos), targetingEnd(false) {}

	void Update(sf::Event& event, float msec);

	~MovingPlatform(){}

private:
	btVector3 startPos;
	btVector3 endPos;
	float moveSpeed;
	
	btVector3 currentTargetPos;
	bool targetingEnd = false;
};

