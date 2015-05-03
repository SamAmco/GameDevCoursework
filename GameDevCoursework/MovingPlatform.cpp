#include "stdafx.h"
#include "MovingPlatform.h"


void MovingPlatform::Update(sf::Event& event, float msec)
{
	btTransform trans = blockRigidBody->getWorldTransform();
	
	btVector3 currentPos = trans.getOrigin();
	btVector3 disp = currentTargetPos - currentPos;
	float sec = msec * .001f;

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