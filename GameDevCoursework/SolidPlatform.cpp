#include "stdafx.h"
#include "SolidPlatform.h"


SolidPlatform::SolidPlatform(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position, Vector3& boxHalfExtents)
	: renderer(renderer), dynamicsWorld(dynamicsWorld)
{
	initializeGraphics(position, boxHalfExtents);
	initializePhysics(position, boxHalfExtents);
}

void SolidPlatform::initializeGraphics(const Vector3& position, const Vector3& boxHalfExtents)
{
	Mesh* m = MeshManager::getInstance().LoadMesh("Meshes/cube.obj");
	Shader* shader = ShaderManager::getInstance().LoadShader("PhongVert", "PhongFrag");
	renderObject = new RenderObject(m, shader);
	renderObject->AddTexture(TextureManager::getInstance().LoadTexture("Textures/smiley.png"));
	scaleMatrix = Matrix4::Scale(boxHalfExtents);
	renderObject->SetModelMatrix(Matrix4::Translation(position) * scaleMatrix);
	renderer.AddRenderObject(renderObject);
}

void SolidPlatform::initializePhysics(const Vector3& position, const Vector3& boxHalfExtents)
{
	blockShape = new btBoxShape(btVector3(boxHalfExtents.x, boxHalfExtents.y, boxHalfExtents.z));

	blockMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(position.x, position.y, position.z)));

	btRigidBody::btRigidBodyConstructionInfo blockRigidBodyCI(0, blockMotionState, blockShape, btVector3(0,0,0));
	blockRigidBody = new btRigidBody(blockRigidBodyCI);

	dynamicsWorld->addRigidBody(blockRigidBody);
}

SolidPlatform::~SolidPlatform()
{
	renderer.RemoveRenderObject(renderObject);
	delete blockShape;
	delete blockRigidBody;
	delete blockMotionState;
	delete renderObject;
}
