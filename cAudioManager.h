#pragma once

#include <unordered_map>
#include <string>

#include "SDL_mixer.h"

class cAudioManager
{
public:
	cAudioManager(const cAudioManager&) = delete;
	inline static cAudioManager* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cAudioManager(); }

	bool LoadAudio(std::string key, const char* filepath, bool isMusic = false);
	void PlayAudio(std::string key, bool isMusic = false);

	inline void SetMusicVolume(int volume) { Mix_VolumeMusic(volume); }
	inline void SetSFXVolume(std::string key, int volume) { if (m_sfxDictionary[key] != nullptr) Mix_VolumeChunk(m_sfxDictionary[key], volume); }

	void Clean();

private:
	cAudioManager() {};
	static cAudioManager* m_Instance;

	std::unordered_map<std::string, Mix_Chunk*> m_sfxDictionary;
	std::unordered_map<std::string, Mix_Music*> m_musicDictionary;
};

