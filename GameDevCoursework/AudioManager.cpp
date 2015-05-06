//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "AudioManager.h"


Resource* AudioManager::LoadResource(const string& name, const int type)
{
	//return the resource if it's already loaded
	for (auto m : loadedResources)
	{
		if (m->name.compare(name) == 0)
			return m;
	}
	//otherwise load the given type of resource with the given name
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
	//when volume is changed, we must change the volume of all loaded audio resources
	//in case any of them are playing
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

	FILE* file;
	stringstream s;
	s << "Audio/" << name;

	if (!music->openFromFile(s.str()))
	{
		//load failed
		delete music;
		cout << "Failed to load music: " << s.str() << endl;
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

	FILE* file;
	stringstream s;
	s << "Audio/" << name;

	if (!soundBuffer->loadFromFile(s.str()))
	{
		delete sound;
		delete soundBuffer;
		cout << "Failed to load sound: " << s.str() << endl;
		sr->failedToLoad = true;
		return sr;
	}
	sound->setBuffer(*soundBuffer);
	sr->soundBuffer = soundBuffer;
	sr->sound = sound;
	loadedResources.push_back(sr);
	return sr;
}