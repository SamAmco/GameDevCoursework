//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "ThirdPersonCamera.h"

//Set the view matrix of the renderer
void ThirdPersonCamera::Update(Renderer& renderer, const Vector3& target)
{
	//get the distance the mouse has traveled and calculate the rotational distance
	rotation += (screenCentre.x - sf::Mouse::getPosition().x) * mouseSensitivity;
	//set the mouse back to the centre of the screen
	sf::Mouse::setPosition(screenCentre);

	//calculate and set the view matrix of the camera
	Matrix4 pos = Matrix4::Translation(-target);
	Matrix4 offset = Matrix4::Translation(-Vector3(0, height, distance));
	Matrix4 rot = Matrix4::Rotation(rotation, Vector3(0,1,0));
	
	renderer.viewMatrix = offset * rot * pos;
}

//rotate a vector by the current camera rotation
btVector3 ThirdPersonCamera::getRotatedVector(Vector3& v)
{
	Matrix4 rot = Matrix4::Rotation(-rotation, Vector3(0, 1, 0));
	Vector3 temp = rot * v;
	return btVector3(temp.x, temp.y, temp.z);
}