#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "btBulletDynamicsCommon.h"

class SolidPlatform
{
public:
	SolidPlatform(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position, Vector3& boxHalfExtents);
	~SolidPlatform();

private:
	void initializeGraphics(const Vector3& position, const Vector3& boxHalfExtents);
	void initializePhysics(const Vector3& position, const Vector3& boxHalfExtents);

	btCollisionShape* blockShape;
	btDefaultMotionState* blockMotionState;
	btRigidBody* blockRigidBody;

	RenderObject* renderObject;
	Renderer& renderer;
	btDiscreteDynamicsWorld* dynamicsWorld;

	Matrix4 scaleMatrix;
};

