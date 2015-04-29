//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "SolidPlatform.h"


SolidPlatform::SolidPlatform(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld,
	const Vector3& position, const Vector3& boxHalfExtents, const string& texName)
	: renderer(renderer), dynamicsWorld(dynamicsWorld)
{
	initializeGraphics(position, boxHalfExtents, texName);
	initializePhysics(position, boxHalfExtents);
}

//Add the render object to the renderer
void SolidPlatform::initializeGraphics(const Vector3& position, const Vector3& boxHalfExtents, const string& texName)
{
	MeshResource* m = (MeshResource*)MeshManager::getInstance().LoadResource("Meshes/cube.obj");
	MaterialResource* mat = (MaterialResource*)MaterialManager::getInstance().LoadResource("PlatformMaterial");
	renderObject = new RenderObject(m, mat);
	renderObject->AddTexture((TextureResource*)TextureManager::getInstance().LoadResource("Textures/" + texName));
	renderObject->SetModelMatrix(Matrix4::Translation(position) * Matrix4::Scale(boxHalfExtents));
	renderer.AddRenderObject(renderObject);
}

//Add the box to the physics world
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
