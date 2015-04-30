#pragma once
#include "AudioResource.h"
#include <SFML/Audio.hpp>

class SoundResource : public AudioResource
{
public:
	SoundResource(){}
	~SoundResource(){ delete sound; delete soundBuffer; }

	inline void setVolume(float v){ sound->setVolume(v); }

	sf::Sound* sound;
	sf::SoundBuffer* soundBuffer;
};

