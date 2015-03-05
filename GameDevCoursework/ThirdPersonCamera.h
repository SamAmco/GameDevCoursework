//File Written by Samuel Amantea-Collins
#pragma once
#include "GraphicsCode\Vector3.h"
#include "GraphicsCode\Renderer.h"
#include "GraphicsCode\Matrix4.h"
#include <SFML/Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Window\VideoMode.hpp>

//A third person camera tracks mouse input and sets the view matrix of the renderer
class ThirdPersonCamera
{
public:
	//store the centre of the screen and initialize other variables
	ThirdPersonCamera(float distance, float height, float mouseSensitivity = 0.1f) 
		: distance(distance), height(height), mouseSensitivity(mouseSensitivity),
		screenCentre(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2)){}
	~ThirdPersonCamera(){}

	void Update(Renderer& renderer, const Vector3& target);

	//This function can be useful e.g. to rotate the torque axis applied to the player character based on the view angle
	btVector3 getRotatedVector(Vector3& v);

	//The distance from the target that the camera should keep on x and z
	float distance;
	//The height above the target that the camera is on y
	float height;

private:
	sf::Vector2i screenCentre;
	float rotation = 0;

	//TODO: potentially could be data driven
	const float mouseSensitivity = 0.1f;
};

