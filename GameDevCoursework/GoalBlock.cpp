#include "stdafx.h"
#include "GoalBlock.h"


GoalBlock::GoalBlock(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position)
	: renderer(renderer), dynamicsWorld(dynamicsWorld)
{
	initializeGraphics(position);
	initializePhysics(position);
}

void GoalBlock::initializeGraphics(const Vector3& position)
{
	Mesh* m = MeshManager::getInstance().LoadMesh("Meshes/cube.obj");
	Shader* shader = ShaderManager::getInstance().LoadShader("PhongVert", "PhongFrag");
	renderObject = new RenderObject(m, shader);
	renderObject->AddTexture(TextureManager::getInstance().LoadTexture("Textures/smiley.png"));
	renderObject->SetModelMatrix(Matrix4::Translation(position));
	renderer.AddRenderObject(renderObject);
}

void GoalBlock::initializePhysics(const Vector3& position)
{
	blockShape = new btBoxShape(btVector3(1,1,1));

	blockMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(position.x, position.y, position.z)));

	btScalar mass = 1;
	btVector3 sphereInertia(0, 0, 0);

	blockShape->calculateLocalInertia(mass, sphereInertia);
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, blockMotionState, blockShape, sphereInertia);
	blockRigidBody = new btRigidBody(sphereRigidBodyCI);
	dynamicsWorld->addRigidBody(blockRigidBody);
}

void GoalBlock::Update(sf::Event& event, float msec)
{
	btTransform trans;
	blockRigidBody->getMotionState()->getWorldTransform(trans);
	Matrix4 m = Matrix4(trans);
	m.SetPositionVector(m.GetPositionVector());
	renderObject->SetModelMatrix(m);
}

GoalBlock::~GoalBlock()
{
	renderer.RemoveRenderObject(renderObject);
	delete renderObject;
	delete blockShape;
	delete blockMotionState;
	delete blockRigidBody;
}
