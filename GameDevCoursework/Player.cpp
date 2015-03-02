#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3& position) 
	: renderer(renderer), dynamicsWorld(dynamicsWorld), camera(ThirdPersonCamera(10, 2))
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
	sphereRigidBody->setFriction(2.0f);
	sphereRigidBody->setDamping(0.01f,0.9f);

	dynamicsWorld->addRigidBody(sphereRigidBody);
}

void Player::Update(sf::Event& event, float msec)
{
	btTransform trans;
	sphereRigidBody->getMotionState()->getWorldTransform(trans);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sphereRigidBody->applyTorque(camera.getRotatedVector(Vector3(-1, 0, 0)) * torquePower);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sphereRigidBody->applyTorque(camera.getRotatedVector(Vector3(1, 0, 0)) * torquePower);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sphereRigidBody->applyTorque(camera.getRotatedVector(Vector3(0, 0, 1)) * torquePower);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sphereRigidBody->applyTorque(camera.getRotatedVector(Vector3(0, 0, -1)) * torquePower);

	//If The player has ground beneath them and they press space, then jump
	btVector3 start = trans.getOrigin() + btVector3(0, -0.9f, 0);
	btVector3 end = trans.getOrigin() + btVector3(0, -1.3f, 0);
	btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
	dynamicsWorld->rayTest(start, end, rayCallback);
	if (rayCallback.hasHit())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			sphereRigidBody->applyImpulse(btVector3(0, jumpPower, 0), btVector3(0, 0, 0));
	}
	//else
		//cout << "not on ground" << endl;

	renderObject->SetModelMatrix(trans);
	camera.Update(renderer, Vector3(trans.getOrigin()));
}

Player::~Player()
{
	renderer.RemoveRenderObject(renderObject);
	delete renderObject;
	delete shpereShape;
	delete sphereMotionState;
	delete sphereRigidBody;
}

