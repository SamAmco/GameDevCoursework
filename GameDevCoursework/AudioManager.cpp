//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "AudioManager.h"


AudioManager::AudioManager()
{
	loadedMusic = vector<MusicResource*>();
	loadedSounds = vector<SoundResource*>();
}

Resource* AudioManager::LoadResource(const string& name, const int type)
{
	switch (type)
	{
		case AUDIO_TYPE::SOUND :
			return LoadSound(name);
		default :
			return LoadMusic(name);
	}
}

//delete all the audio objects from the heap and clear the maps
void AudioManager::UnloadAllResources()
{
	//delete loaded sounds
	for (auto s : loadedSounds)
	{
		cout << "deleting " << s->name << endl;
		delete s->soundBuffer;
		delete s->sound;
		delete s;
	}
	loadedSounds.clear();

	//delete loaded music
	for (auto m : loadedMusic)
	{
		cout << "deleting " << m->name << endl;
		delete m->music;
		delete m;
	}
	loadedMusic.clear();
}

void AudioManager::LoadingNewScene()
{
	auto iter = loadedSounds.begin();
	//delete loaded sounds
	while (iter != loadedSounds.end())
	{
		if ((*iter)->destroyOnSceneLoad)
		{
			cout << "deleting " << (*iter)->name << endl;
			delete (*iter)->soundBuffer;
			delete (*iter)->sound;
			delete *iter;
			iter = loadedSounds.erase(iter);
		}
		else ++iter;
	}

	auto iter2 = loadedMusic.begin();
	//delete loaded sounds
	while (iter2 != loadedMusic.end())
	{
		if ((*iter2)->destroyOnSceneLoad)
		{
			cout << "deleting " << (*iter2)->name << endl;
			delete (*iter2)->music;
			delete *iter2;
			iter2 = loadedMusic.erase(iter2);
		}
		else ++iter2;
	}
}

MusicResource* AudioManager::LoadMusic(const string& name)
{
	//if we have already loaded the Music object, then return that
	for (auto m : loadedMusic)
	{
		if (m->name.compare(name))
			return m;
	}

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
	loadedMusic.push_back(mr);
	return mr;
}

SoundResource* AudioManager::LoadSound(const string& name)
{
	//if we have already loaded the Sound object, then return that
	for (auto s : loadedSounds)
	{
		if (s->name.compare(name))
			return s;
	}

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
	loadedSounds.push_back(sr);
	return sr;
}