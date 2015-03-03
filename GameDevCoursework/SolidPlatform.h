#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "btBulletDynamicsCommon.h"

class SolidPlatform
{
public:
	SolidPlatform(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, 
		const Vector3& position, const Vector3& boxHalfExtents, const string& texName);
	~SolidPlatform();

private:
	void initializeGraphics(const Vector3& position, const Vector3& boxHalfExtents, const string& texName);
	void initializePhysics(const Vector3& position, const Vector3& boxHalfExtents);

	btCollisionShape* blockShape;
	btDefaultMotionState* blockMotionState;
	btRigidBody* blockRigidBody;

	RenderObject* renderObject;
	Renderer& renderer;
	btDiscreteDynamicsWorld* dynamicsWorld;

	Matrix4 scaleMatrix;
};

