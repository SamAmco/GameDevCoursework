#pragma once
#include "Resource.h"
#include <SFML/Audio.hpp>

class MusicResource : public Resource
{
public:
	MusicResource(){}
	~MusicResource(){ delete music; }

	sf::Music* music;
};

