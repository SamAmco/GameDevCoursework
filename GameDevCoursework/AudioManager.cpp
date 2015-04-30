//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "AudioManager.h"

Resource* AudioManager::LoadResource(const string& name, const int type)
{
	for (auto m : loadedResources)
	{
		if (m->name.compare(name) == 0)
			return m;
	}
	switch (type)
	{
		case AUDIO_TYPE::SOUND :
			return LoadSound(name);
		default :
			return LoadMusic(name);
	}
}

void AudioManager::PlayMusicResource(MusicResource* music)
{
	music->music->setVolume(volume);
	music->music->play();
}

void AudioManager::PlaySoundResource(SoundResource* sound)
{
	sound->sound->setVolume(volume);
	sound->sound->play();
}

void AudioManager::setVolume(float v)
{
	volume = v;
	for (auto r : loadedResources)
	{
		AudioResource* a = (AudioResource*)r;
		a->setVolume(v);
	}
}

MusicResource* AudioManager::LoadMusic(const string& name)
{
	cout << "Loading Music: " << name << endl;
	//otherwise attempt to load it
	sf::Music* music = new sf::Music();
	MusicResource* mr = new MusicResource();

	if (!music->openFromFile(name))
	{
		//load failed
		delete music;
		cout << "Failed to load music: " << name << endl;
		mr->failedToLoad = true;
		return mr;
	}
	mr->music = music;
	mr->name = name;
	loadedResources.push_back(mr);
	return mr;
}

SoundResource* AudioManager::LoadSound(const string& name)
{
	cout << "Loading Sound: " << name << endl;
	//otherwise attempt to load it
	sf::Sound* sound = new sf::Sound();
	//Sound objects require a SoundBuffer object also
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();

	SoundResource* sr = new SoundResource();

	if (!soundBuffer->loadFromFile(name))
	{
		delete sound;
		delete soundBuffer;
		cout << "Failed to load sound: " << name << endl;
		sr->failedToLoad = true;
		return sr;
	}
	sound->setBuffer(*soundBuffer);
	sr->soundBuffer = soundBuffer;
	sr->sound = sound;
	loadedResources.push_back(sr);
	return sr;
}