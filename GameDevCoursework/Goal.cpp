//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Goal.h"

//store a reference to the renderer and player and initialize the graphics
Goal::Goal(Renderer& renderer, Player& player, Vector3& position)
	: renderer(renderer), player(player)
{
	initializeGraphics(position);
	this->position = btVector3(position.x, position.y, position.z);
}

//add the render object to the renderer
void Goal::initializeGraphics(const Vector3& position)
{
	Mesh* m = MeshManager::getInstance().LoadMesh("Meshes/goalCylinder.obj");
	Shader* shader = ShaderManager::getInstance().LoadShader("BasicVert", "TransparentTex");
	renderObject = new RenderObject(m, shader);
	renderObject->AddTexture(TextureManager::getInstance().LoadTexture("Textures/goalLight.png"));
	renderObject->SetModelMatrix(Matrix4::Translation(position));
	renderer.AddRenderObject(renderObject);
}

//if the player is within the win threshold, return true 
bool Goal::Update(sf::Event& event, float msec)
{
	if ((player.sphereRigidBody->getWorldTransform().getOrigin() - position).length2() < WIN_THRESHOLD)
		return true;
	return false;
}

Goal::~Goal()
{
	renderer.RemoveRenderObject(renderObject);
	delete renderObject;
}
