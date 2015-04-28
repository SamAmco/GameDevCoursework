#pragma once
#include "Resource.h"
#include <SFML/Audio.hpp>

class MusicResource : public Resource
{
public:
	MusicResource(){}
	~MusicResource(){}

	sf::Music* music;
};

