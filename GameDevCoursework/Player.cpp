#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position) 
	: renderer(renderer), dynamicsWorld(dynamicsWorld), camera(ThirdPersonCamera(8, 2))
{
	initializeGraphics(position);
	initializePhysics(position);
}

void Player::initializeGraphics(const Vector3& position)
{ 
	Mesh* m = MeshManager::getInstance().LoadMesh("Meshes/sphere.obj");
	Shader* shader = ShaderManager::getInstance().LoadShader("PhongVert", "PhongFrag");
	renderObject = new RenderObject(m, shader);
	renderObject->AddTexture(TextureManager::getInstance().LoadTexture("Textures/smiley.png"));
	renderObject->SetModelMatrix(Matrix4::Translation(position));
	renderer.AddRenderObject(renderObject);
}

void Player::initializePhysics(const Vector3& position)
{
	shpereShape = new btSphereShape(1);

	sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(position.x, position.y, position.z)));
	
	btScalar mass = 1;
	btVector3 sphereInertia(0, 0, 0);

	shpereShape->calculateLocalInertia(mass, sphereInertia);
	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, shpereShape, sphereInertia);
	sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	sphereRigidBody->setActivationState(DISABLE_DEACTIVATION);
	dynamicsWorld->addRigidBody(sphereRigidBody);
}

void Player::Update(sf::Event& event, float msec)
{
	//cout << Vector3(sphereRigidBody->getAngularVelocity()) << " : ";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sphereRigidBody->applyTorque(btVector3(-1, 0, 0) * torquePower);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sphereRigidBody->applyTorque(btVector3(1, 0, 0) * torquePower);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sphereRigidBody->applyTorque(btVector3(0, 0, 1) * torquePower);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sphereRigidBody->applyTorque(btVector3(0, 0, -1) * torquePower);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		sphereRigidBody->applyImpulse(btVector3(0, jumpPower, 0), btVector3());

	float camSpeed = 0.4f;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	renderer.SetViewMatrix(renderer.viewMatrix * Matrix4::Rotation(-camSpeed, Vector3(0, 1, 0)));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	renderer.SetViewMatrix(renderer.viewMatrix * Matrix4::Rotation(camSpeed, Vector3(0, 1, 0)));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//	renderer.SetViewMatrix(renderer.viewMatrix * Matrix4::Rotation(-camSpeed, Vector3(1, 0, 0)));
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//	renderer.SetViewMatrix(renderer.viewMatrix * Matrix4::Rotation(camSpeed, Vector3(1, 0, 0)));

	btTransform trans;
	sphereRigidBody->getMotionState()->getWorldTransform(trans);
	renderObject->SetModelMatrix(trans);
	//cout << Vector3(trans.getOrigin()) << endl;
	camera.Update(renderer, Vector3(trans.getOrigin()));
}

Player::~Player()
{
	renderer.RemoveRenderObject(renderObject);
	delete renderObject;
	delete shpereShape;
	delete sphereMotionState;
}

