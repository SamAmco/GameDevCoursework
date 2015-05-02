//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "SolidPlatform.h"


SolidPlatform::SolidPlatform(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld,
	btVector3& position, btQuaternion& rotation, btVector3& boxHalfExtents, const string& texName)
	: renderer(renderer), dynamicsWorld(dynamicsWorld)
{
	initializeGraphics(position, rotation, boxHalfExtents, texName);
	initializePhysics(position, rotation, boxHalfExtents);
}

//Add the render object to the renderer
void SolidPlatform::initializeGraphics(const btVector3& position, const btQuaternion& rotation, const Vector3& boxHalfExtents, const string& texName)
{
	MeshResource* m = (MeshResource*)MeshManager::getInstance().LoadResource("Meshes/cube.obj");
	MaterialResource* mat = (MaterialResource*)MaterialManager::getInstance().LoadResource("PlatformMaterial");
	renderObject = new RenderObject(m, mat);
	renderObject->AddTexture((TextureResource*)TextureManager::getInstance().LoadResource("Textures/" + texName));
	btTransform trans = btTransform(rotation, position);
	renderObject->SetModelMatrix(Matrix4(trans) * Matrix4::Scale(boxHalfExtents));
	renderer.AddRenderObject(renderObject);
}

//Add the box to the physics world
void SolidPlatform::initializePhysics(const btVector3& position, const btQuaternion& rotation, const btVector3& boxHalfExtents)
{
	blockShape = new btBoxShape(boxHalfExtents);

	blockMotionState = new btDefaultMotionState(btTransform(rotation, position));

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
