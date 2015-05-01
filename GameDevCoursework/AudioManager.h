//File Written by Samuel Amantea-Collins
#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <iostream>
#include "ResourceManager.h"
#include "MusicResource.h"
#include "SoundResource.h"

using namespace std;

enum AUDIO_TYPE
{
	SOUND,
	MUSIC
};

//The AudioManager is a singleton used for loading and caching audio files and 
//managing the memory they use.
class AudioManager : public ResourceManager
{
public:
	//Provides support for two different types of Audio
	//Sounds are loaded directly into memory, music is streamed from the hard disk
	Resource* LoadResource(const string& name, const int type = 0);

	void PlayMusicResource(MusicResource* music);
	void PlaySoundResource(SoundResource* sound);
	void setVolume(float v);
	inline float getVolume(){ return volume; }

	//singleton getter
	static AudioManager& getInstance()
	{
		static AudioManager instance;
		return instance;
	}

	~AudioManager(){ UnloadAllResources(); }

private:
	//These store mappings of audio to name, so we know what we've loaded already
	AudioManager(){};
	SoundResource* LoadSound(const string& name);
	MusicResource* LoadMusic(const string& name);
	float volume = 0.f;//100.f;
};

