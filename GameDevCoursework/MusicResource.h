//File Written by Samuel Amantea-Collins
#pragma once
#include "AudioResource.h"
#include <SFML/Audio.hpp>

//Stores and destroys an sf::Music object
class MusicResource : public AudioResource
{
public:
	MusicResource(){}
	~MusicResource(){ delete music; }

	inline void setVolume(float v){ music->setVolume(v); }

	sf::Music* music;
};

