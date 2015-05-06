//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "MovingPlatform.h"


void MovingPlatform::Update(sf::Event& event, float msec)
{
	//each frame we need to move the block towards its current target
	btTransform trans = blockRigidBody->getWorldTransform();
	
	btVector3 currentPos = trans.getOrigin();
	btVector3 disp = currentTargetPos - currentPos;
	float sec = msec * .001f;

	//if the block is at its current target, switch its current target
	if (disp.length2() < (moveSpeed * sec) * (moveSpeed * sec))
	{
		currentPos = currentTargetPos;
		currentTargetPos = targetingEnd ? startPos : endPos;
		targetingEnd = !targetingEnd;
	}
	else
		currentPos += moveSpeed * disp.normalized() * sec;

	trans.setOrigin(currentPos);
	
	blockRigidBody->setWorldTransform(trans);
	renderObject->SetModelMatrix(Matrix4(trans) * Matrix4::Scale(boxHalfExtents));
}