//File Written by Samuel Amantea-Collins
#pragma once
#include "AudioResource.h"
#include <SFML/Audio.hpp>

//Stores and destroys a sound object
class SoundResource : public AudioResource
{
public:
	SoundResource(){}
	~SoundResource(){ delete sound; delete soundBuffer; }

	inline void setVolume(float v){ sound->setVolume(v); }

	sf::Sound* sound;
	sf::SoundBuffer* soundBuffer;
};

