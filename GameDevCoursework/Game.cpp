#include "stdafx.h"
#include "Game.h"

#include "MeshManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

Game::Game(Renderer& renderer)
	: renderer(renderer)
{
	initializeGraphics();
	initializePhysics();
}

void Game::initializeGraphics()
{
	Mesh* m = MeshManager::getInstance().LoadMesh("Meshes/sphere.obj");

	Shader* shader = ShaderManager::getInstance().LoadShader("PhongVert", "PhongFrag");

	o = RenderObject(m, shader);
	o.AddTexture(TextureManager::getInstance().LoadTexture("Textures/smiley.png"));
	o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
	renderer.AddRenderObject(o);

	lightCol = Vector3(1, 1, 1);
	lightPos = Vector3(20.0f, 20.0f, -10);
	lightRad = 3000.0f;

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));
}

void Game::initializePhysics()
{
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));


	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	btCollisionShape* fallShape = new btSphereShape(1);


	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -3, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);


	btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 3, -10)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	sphereRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(sphereRigidBody);
}

void Game::Update(sf::Event event, float msec)
{
	dynamicsWorld->stepSimulation(msec);

	btTransform trans;
	sphereRigidBody->getMotionState()->getWorldTransform(trans);

	Vector3 pos = Vector3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
	cout << pos << endl;
	o.SetModelMatrix(Matrix4::Translation(pos));
}

Game::~Game()
{
}
