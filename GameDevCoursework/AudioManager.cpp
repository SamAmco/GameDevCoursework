//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "AudioManager.h"


AudioManager::AudioManager()
{
	loadedMusic = map<string, sf::Music*>();
	loadedSounds = map<string, sf::Sound*>();
	buffers = vector<sf::SoundBuffer*>();
}

//delete all the audio objects from the heap and clear the maps
void AudioManager::UnloadAudio()
{
	//delete loaded sounds
	map<string, sf::Sound*>::const_iterator i1 = loadedSounds.begin();
	while (i1 != loadedSounds.end())
	{
		cout << "deleting " << i1->first << endl;
		delete i1->second;
		++i1;
	}
	loadedSounds.clear();

	//delete loaded buffers
	for (auto s : buffers)
	{
		delete s;
	}
	buffers.clear();

	//delete loaded music
	map<string, sf::Music*>::const_iterator i2 = loadedMusic.begin();
	while (i2 != loadedMusic.end())
	{
		cout << "deleting " << i2->first << endl;
		delete i2->second;
		++i2;
	}
	loadedMusic.clear();
}

sf::Music* AudioManager::LoadMusic(string name)
{
	//if we have already loaded the Music object, then return that
	map<string, sf::Music*>::const_iterator i = loadedMusic.find(name);
	if (i != loadedMusic.end())
		return (*i).second;

	//otherwise attempt to load it
	sf::Music* music = new sf::Music();
	if (!music->openFromFile(name))
	{
		//load failed
		delete music;
		cout << "Failed to load music: " << name << endl;
		return NULL;
	}
	loadedMusic.insert(pair<string, sf::Music*>(name, music));
	return music;
}

sf::Sound* AudioManager::LoadSound(string name)
{
	//if we have already loaded the Sound object, then return that
	map<string, sf::Sound*>::const_iterator i = loadedSounds.find(name);
	if (i != loadedSounds.end())
		return (*i).second;

	//otherwise attempt to load it
	sf::Sound* sound = new sf::Sound();
	//Sound objects require a SoundBuffer object also
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();

	if (!soundBuffer->loadFromFile(name))
	{
		delete sound;
		delete soundBuffer;
		cout << "Failed to load sound: " << name << endl;
		return NULL;
	}
	buffers.push_back(soundBuffer);
	sound->setBuffer(*soundBuffer);
	loadedSounds.insert(pair<string, sf::Sound*>(name, sound));
	return sound;
}

AudioManager::~AudioManager()
{
	//Just in case
	UnloadAudio();
}
