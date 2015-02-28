#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position) 
	: renderer(renderer), dynamicsWorld(dynamicsWorld)
{
	initializeGraphics(position);
	initializePhysics(position);
}

void Player::initializeGraphics(const Vector3& position)
{ 
	Mesh* m = MeshManager::getInstance().LoadMesh("Meshes/sphere.obj");
	Shader* shader = ShaderManager::getInstance().LoadShader("PhongVert", "PhongFrag");
	renderObject = RenderObject(m, shader);
	renderObject.AddTexture(TextureManager::getInstance().LoadTexture("Textures/smiley.png"));
	renderObject.SetModelMatrix(Matrix4::Translation(position));
	renderer.AddRenderObject(renderObject);
}

void Player::initializePhysics(const Vector3& position)
{
	btCollisionShape* shpereShape = new btSphereShape(1);

	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(position.x, position.y, position.z)));
	
	btScalar mass = 1;
	btVector3 sphereInertia(0, 0, 0);

	shpereShape->calculateLocalInertia(mass, sphereInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, sphereMotionState, shpereShape, sphereInertia);
	sphereRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(sphereRigidBody);
}

void Player::Update(sf::Event& event, float msec)
{
	btTransform trans;
	sphereRigidBody->getMotionState()->getWorldTransform(trans);
	//cout << Matrix4(trans) << endl;
	renderObject.SetModelMatrix(trans);
}

Player::~Player()
{
}

