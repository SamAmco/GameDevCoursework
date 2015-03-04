//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Vector3.h"
#include "GraphicsCode\Renderer.h"
#include "GraphicsCode\Matrix4.h"
#include <SFML/Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Window\VideoMode.hpp>

class ThirdPersonCamera
{
public:
	ThirdPersonCamera(float distance, float height, float mouseSensitivity = 0.1f) 
		: distance(distance), height(height), mouseSensitivity(mouseSensitivity),
		screenCentre(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2)){}
	~ThirdPersonCamera(){}

	void Update(Renderer& renderer, const Vector3& target);
	btVector3 getRotatedVector(Vector3& v);


	float distance;
	float height;

private:
	sf::Vector2i screenCentre;
	float rotation = 0;
	float mouseSensitivity = 0.1f;
};

