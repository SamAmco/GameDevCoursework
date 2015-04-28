#pragma once
#include "Resource.h"
#include <SFML/Audio.hpp>

class SoundResource : public Resource
{
public:
	SoundResource(){}
	~SoundResource(){}

	sf::Sound* sound;
	sf::SoundBuffer* soundBuffer;
};

