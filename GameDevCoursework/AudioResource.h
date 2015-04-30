#pragma once
#include "Resource.h"
#include <SFML/Audio.hpp>

class AudioResource : public Resource
{
public:
	AudioResource(){}
	virtual ~AudioResource(){}

	virtual void setVolume(float v) = 0;
};
