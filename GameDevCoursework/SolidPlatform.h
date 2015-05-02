//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "MaterialManager.h"
#include "btBulletDynamicsCommon.h"

//A solid platform is just a wrapper for a cube that makes it easy to define a static cube in the world
//with a given texture and size
class SolidPlatform
{
public:
	SolidPlatform(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld,
		btVector3& position, btQuaternion& rotation, btVector3& boxHalfExtents, const string& texName);
	~SolidPlatform();

private:
	void initializeGraphics(const btVector3& position, const btQuaternion& rotation, const Vector3& boxHalfExtents, const string& texName);
	void initializePhysics(const btVector3& position, const btQuaternion& rotation, const btVector3& boxHalfExtents);

	btCollisionShape* blockShape;
	btDefaultMotionState* blockMotionState;
	btRigidBody* blockRigidBody;
	btDiscreteDynamicsWorld* dynamicsWorld;

	RenderObject* renderObject;
	Renderer& renderer;
};

