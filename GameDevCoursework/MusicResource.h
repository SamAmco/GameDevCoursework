#pragma once
#include "AudioResource.h"
#include <SFML/Audio.hpp>

class MusicResource : public AudioResource
{
public:
	MusicResource(){}
	~MusicResource(){ delete music; }

	inline void setVolume(float v){ music->setVolume(v); }

	sf::Music* music;
};

