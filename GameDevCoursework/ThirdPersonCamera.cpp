#include "stdafx.h"
#include "ThirdPersonCamera.h"

void ThirdPersonCamera::Update(Renderer& renderer, const Vector3& target)
{
	rotation += (screenCentre.x - sf::Mouse::getPosition().x) * mouseSensitivity;
	sf::Mouse::setPosition(screenCentre);

	Matrix4 pos = Matrix4::Translation(-target);
	Matrix4 offset = Matrix4::Translation(-Vector3(0, height, distance));
	Matrix4 rot = Matrix4::Rotation(rotation, Vector3(0,1,0));
	
	renderer.viewMatrix = offset * rot * pos;
}

btVector3 ThirdPersonCamera::getRotatedVector(Vector3& v)
{
	Matrix4 rot = Matrix4::Rotation(-rotation, Vector3(0, 1, 0));
	Vector3 temp = rot * v;
	return btVector3(temp.x, temp.y, temp.z);
}