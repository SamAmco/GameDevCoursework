//File Written by Samuel Amantea-Collins
#pragma once
#include "Resource.h"
#include <SFML/Audio.hpp>

//The resource type that SoundResource and MusicResource inherit
//provides functionality for setting volume
class AudioResource : public Resource
{
public:
	AudioResource(){}
	virtual ~AudioResource(){}

	virtual void setVolume(float v) = 0;
};
