#include <iostream>

#include "cAudioManager.h"

cAudioManager* cAudioManager::m_Instance = nullptr;

// INFO: If isMusic is false then the audio provided will be loaded as a Mix_Chunk (SFX)
bool cAudioManager::LoadAudio(std::string key, const char* filepath, bool isMusic)
{
	if (isMusic)
	{
		Mix_Music* music = Mix_LoadMUS(filepath);

		if (music == nullptr)
		{
			std::cout << "Failed to initialise music. SDL_Mix error: " << Mix_GetError() << std::endl;
			return false;
		}

		m_musicDictionary[key] = music;
	}
	else
	{
		Mix_Chunk* sfx = Mix_LoadWAV(filepath);

		if (sfx == nullptr)
		{
			std::cout << "Failed to initialise sfx. SDL_Mix error: " << Mix_GetError() << std::endl;
			return false;
		}

		m_sfxDictionary[key] = sfx;
	}
	return true;
}

// INFO: If isMusic is false then the key provided will be searched in the SFX dictionary and if found an SFX will be played
void cAudioManager::PlayAudio(std::string key, bool isMusic)
{
	if (isMusic)
	{
		if (m_musicDictionary[key] != nullptr)
		{
			if (Mix_PlayMusic(m_musicDictionary[key], -1) == -1)
				std::cout << "Music could not be played. SDL_Mixer error: " << Mix_GetError() << std::endl;

			m_currentMusic = key;
		}
	}
	else
	{
		if (m_sfxDictionary[key] != nullptr)
		{
			if (Mix_PlayChannel(-1, m_sfxDictionary[key], 0) == -1)
				std::cout << "SFX could not be played. SDL_Mixer error: " << Mix_GetError() << std::endl;
		}
	}
}

void cAudioManager::Clean()
{
	for (auto i = m_musicDictionary.begin(); i != m_musicDictionary.end(); i++)
	{
		Mix_FreeMusic(i->second);
	}

	m_musicDictionary.clear();

	if (m_musicDictionary.empty())
		std::cout << "Music Dictionary is empty!" << std::endl;
	else
		std::cout << "Music Dictionary is not empty!" << std::endl;

	for (auto i = m_sfxDictionary.begin(); i != m_sfxDictionary.end(); i++)
	{
		Mix_FreeChunk(i->second);
	}

	m_sfxDictionary.clear();

	if (m_sfxDictionary.empty())
		std::cout << "SFX Dictionary is empty!" << std::endl;
	else
		std::cout << "SFX Dictionary is not empty!" << std::endl;

	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}
