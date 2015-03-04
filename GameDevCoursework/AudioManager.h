//File Written by Samuel Amantea-Collins
#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <iostream>

using namespace std;

//The AudioManager is a singleton used for loading and caching audio files and 
//managing the memory they use.
class AudioManager
{
public:
	~AudioManager();

	//Provides support for two different types of Audio
	//Sounds are loaded directly into memory, music is streamed from the hard disk
	sf::Sound* LoadSound(string name);
	sf::Music* LoadMusic(string name);

	//singleton getter
	static AudioManager& getInstance()
	{
		static AudioManager instance;
		return instance;
	}

	void UnloadAudio();

private:
	//These parts enforce singleton constraints
	AudioManager();
	AudioManager(AudioManager const&) = delete;
	void operator=(AudioManager const&) = delete;

	//These store mappings of audio to name, so we know what we've loaded already
	map<string, sf::Sound*> loadedSounds;
	map<string, sf::Music*> loadedMusic;
	vector<sf::SoundBuffer*> buffers;
};

