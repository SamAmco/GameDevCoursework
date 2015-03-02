#pragma once
#include "GraphicsCode\Renderer.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "btBulletDynamicsCommon.h"

class GoalBlock
{
public:
	GoalBlock(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position);
	~GoalBlock();

	void Update(sf::Event& event, float msec);

private:
	void initializeGraphics(const Vector3& position);
	void initializePhysics(const Vector3& position);

	btCollisionShape* blockShape;
	btDefaultMotionState* blockMotionState;
	btRigidBody* blockRigidBody;
	
	RenderObject* renderObject;
	Renderer& renderer;
	btDiscreteDynamicsWorld* dynamicsWorld;

};

