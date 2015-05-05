//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Player.h"


Player::Player(Renderer& renderer, btDiscreteDynamicsWorld* dynamicsWorld, Vector3 position) 
	: renderer(renderer), dynamicsWorld(dynamicsWorld), camera(ThirdPersonCamera(10, 2))
{
	initializeGraphics(position);
	initializePhysics(position);
}

//Add the RenderObject to the renderer
void Player::initializeGraphics(const Vector3& position)
{ 
	MeshResource* m = (MeshResource*)MeshManager::getInstance().LoadResource("sphere.obj");
	MaterialResource* mat = (MaterialResource*)MaterialManager::getInstance().LoadResource("PlayerMaterial");
	renderObject = new RenderObject(m, mat);
	renderObject->AddTexture((TextureResource*)TextureManager::getInstance().LoadResource("8Ball.png", TextureType::TEXTURE));
	renderObject->SetModelMatrix(Matrix4::Translation(position));
	renderer.AddRenderObject(renderObject);
}

//add the sphereRigidBody to the dynamicsWorld
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

//handle user input for the player
void Player::Update(sf::Event& event, float msec)
{
	//This is useful to regain control of the mouse
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
	{
		hasControl = !hasControl;
	}

	btTransform trans;
	sphereRigidBody->getMotionState()->getWorldTransform(trans);
	renderObject->SetModelMatrix(trans);

	if (hasControl)
	{
		//WASD controls .. the torque is applied around the respective axis rotated by the camera's rotation
		//so that W is always forward with respect to the camera's view etc.
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

		camera.Update(renderer, Vector3(trans.getOrigin()));
	}
}

Player::~Player()
{
	renderer.RemoveRenderObject(renderObject);
	delete renderObject;
	delete shpereShape;
	delete sphereMotionState;
	delete sphereRigidBody;
}

