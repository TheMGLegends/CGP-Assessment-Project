#include <fstream>
#include <iostream>
#include <string>

#include "cAssetManager.h"
#include "cAudioManager.h"
#include "cBulletBill.h"
#include "cCamera.h"
#include "cCollisionManager.h"
#include "cEntityManager.h"
#include "sGlobalStrings.h"
#include "cGoomba.h"
#include "cInputManager.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cPickups.h"
#include "cUILabel.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "cGame.h"

#include "MemoryLeakDetector.h"

cPlayer* Mario = nullptr;
cBulletBill* BulletBill = nullptr;
cUILabel* ScoreCounter = nullptr;

std::vector<cCharacter*> entities;
std::vector<cPickups*> pickups;

// INFO: 2D Map Array used to store tile map data (lvl1) & entity data (lvl1Entities)
std::vector< std::vector<int> > lvl1 = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0},
{0,0,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,5,0,0,0,5,0,0,0,5,0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,4,5,4,0,0,0,0,0,2,2,0,0,0,7,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,7,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,7,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,2,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

std::vector< std::vector<int> > lvl1Entities = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

cGame* cGame::m_Instance = nullptr;

cGame::cGame()
{
	m_window = nullptr;
	m_renderer = nullptr;

	m_bIsRunning = false;

	m_bLevelCompleted = false;
	m_levelCompleteTime = 0.0f;
	m_bonusScore = 0;

	m_currentTime = 0.0f;
	m_resetTime = 0.0f;
}

bool cGame::Initialise(const char* windowTitle, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		// INFO: Window Creation
		m_window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, NULL);
	
		if (m_window == nullptr) 
		{
			std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		// INFO: Renderer Creation
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
		if (m_renderer == nullptr) 
		{
			std::cout << "Failed to create renderer. SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		// INFO: Initialise SDL_Image
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;

		if (IMG_Init(flags) != flags)
		{
			std::cout << "Failed to initialise SDL_Image. SDL_Image error: " << IMG_GetError() << std::endl;
			return false;
		}

		// INFO: Initialise SDL_Mixer
		flags = MIX_INIT_MP3;

		if (Mix_Init(flags) != flags)
		{
			std::cout << "Failed to initialise SDL_Mixer. SDL_Mixer error: " << Mix_GetError() << std::endl;
			return false;
		}

		if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0)
		{
			std::cout << "Failed to open audio device. SDL_Mixer error: " << Mix_GetError() << std::endl;
			return false;
		}

		// INFO: Initialise SDL_TTF
		if (TTF_Init() < 0)
		{
			std::cout << "Failed to initialise SDL_TTF. SDL_TTF error: " << TTF_GetError() << std::endl;
			return false;
		}
	
		// INFO: Initial Window Background Colour
		SDL_SetRenderDrawColor(m_renderer, 92, 148, 252, 255);
	
		// INFO: Enable the Game Loop
		m_bIsRunning = true;

		// INFO: Initialise Textures
		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Tilemap, "Assets/Graphics/Tilemap.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Background, "Assets/Graphics/Background.png", m_renderer);

		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Mario_Idle, "Assets/Graphics/Mario_Idle.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Mario_Run, "Assets/Graphics/Mario_Run.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Mario_Jump, "Assets/Graphics/Mario_Jump.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Mario_Fall, "Assets/Graphics/Mario_Fall.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Mario_Death, "Assets/Graphics/Mario_Death.png", m_renderer);

		cAssetManager::Instance()->LoadTexture(sGlobalStrings::BulletBill_Fly, "Assets/Graphics/BulletBill_Fly.png", m_renderer);

		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Goomba_Walk, "Assets/Graphics/Goomba_Walk.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Goomba_Death, "Assets/Graphics/Goomba_Death.png", m_renderer);

		cAssetManager::Instance()->LoadTexture(sGlobalStrings::Coin_Rotating, "Assets/Graphics/Coin_Rotating.png", m_renderer);

		// INFO: Initialise Fonts
		cAssetManager::Instance()->LoadFont(sGlobalStrings::PixelArt_Font, "Assets/Fonts/PixelArt_Font.fon", 16);

		// INFO: Initialise Music and SFX
		cAudioManager::Instance()->LoadAudio(sGlobalStrings::GroundTheme_Music, "Assets/Audio/GroundTheme_Music.mp3", true);
		cAudioManager::Instance()->LoadAudio(sGlobalStrings::LevelComplete_Music, "Assets/Audio/LevelComplete_Music.mp3", true);

		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Mario_Death_SFX, "Assets/Audio/Mario_Death_SFX.mp3");
		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Mario_GoombaStomp_SFX, "Assets/Audio/Mario_GoombaStomp_SFX.mp3");
		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Mario_Jump_SFX, "Assets/Audio/Mario_Jump_SFX.mp3");

		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Coin_SFX, "Assets/Audio/Coin_SFX.mp3");

		// INFO: Load Entities & Elements
		Mario = new cPlayer(new sEssentials(25, 300, 18, 33, sGlobalStrings::Mario_Idle));
		BulletBill = new cBulletBill(new sEssentials(2950, 350, 16, 16, sGlobalStrings::BulletBill_Fly, SDL_FLIP_HORIZONTAL));
		ScoreCounter = new cUILabel(0, 0, 3, "Score: 0");

		// INFO: Load Map
		cMap::Instance()->LoadMap(lvl1);

		// INFO: Load Entities
		cEntityManager::Instance()->LoadEntities(lvl1Entities);
		entities = cEntityManager::Instance()->GetEntities();
		pickups = cEntityManager::Instance()->GetPickups();

		// INFO: Set Camera Target
		cCamera::Instance()->SetTarget(Mario->GetCenterPoint());

		// INFO: Set Audio Volumes
		cAudioManager::Instance()->SetMusicVolume(20);
		cAudioManager::Instance()->SetSFXVolume(sGlobalStrings::Mario_Jump_SFX, 3);
		cAudioManager::Instance()->SetSFXVolume(sGlobalStrings::Mario_Death_SFX, 20);
		cAudioManager::Instance()->SetSFXVolume(sGlobalStrings::Mario_GoombaStomp_SFX, 50);
		cAudioManager::Instance()->SetSFXVolume(sGlobalStrings::Coin_SFX, 25);

		// INFO: Start Music
		cAudioManager::Instance()->PlayAudio(sGlobalStrings::GroundTheme_Music, true);

		return true;
	}
	else 
	{
		std::cout << "Failed to initialize SDL. SDL error: " << SDL_GetError() << std::endl;
		m_bIsRunning = false; // INFO: Security Measure
		return false;
	}
}

void cGame::HandleEvents()
{
	cInputManager::Instance()->Update();
}

void cGame::Update(float deltaTime)
{
	m_currentTime = SDL_GetTicks() - m_resetTime;

	if (m_bLevelCompleted)
	{
		m_levelCompleteTime += deltaTime;

		if (cAudioManager::Instance()->GetCurrentMusic() == sGlobalStrings::GroundTheme_Music)
		{
			cAudioManager::Instance()->PlayAudio(sGlobalStrings::LevelComplete_Music, true);

			// INFO: Percent Lost every 5 seconds
			float bonusPercentage = 1 - (((m_currentTime / static_cast<float>(1000)) / 5) / 100);
			m_bonusScore = static_cast<int>(TIME_BONUS * bonusPercentage);

			int totalScore = Mario->GetScore() + m_bonusScore;

			// INFO: Read Value Held to determine if high score is the highest score
			std::ifstream Read_Highscore_Holder("Highscore_Holder.txt");
			std::string highscoreTxt;
			std::getline(Read_Highscore_Holder, highscoreTxt);
			Read_Highscore_Holder.close();

			if (stoi(highscoreTxt) < totalScore)
			{
				std::ofstream Write_Highscore_Holder("Highscore_Holder.txt");
				Write_Highscore_Holder << std::to_string(totalScore);
				Write_Highscore_Holder.close();

				std::ifstream Read_Highscore_Holder("Highscore_Holder.txt");
				std::getline(Read_Highscore_Holder, highscoreTxt);
				Read_Highscore_Holder.close();

			}

			std::string temp = "High Score: " + highscoreTxt + "    " + "Score: " + std::to_string(totalScore);
			ScoreCounter->ChangeText(temp);
		}

		// INFO: Centre of Screen
		ScoreCounter->ChangeLabelPos((static_cast<float>(SCREEN_WIDTH) / 2) - ScoreCounter->GetWidth() * 1.5f,
									 (static_cast<float>(SCREEN_HEIGHT / 2) - static_cast<float>(ScoreCounter->GetHeight() / 2)));

		if (m_levelCompleteTime > LEVEL_COMPLETE_INTERVAL)
		{
			m_levelCompleteTime = 0.0f;
			m_bLevelCompleted = false;

			cAudioManager::Instance()->PlayAudio(sGlobalStrings::GroundTheme_Music, true);

			ResetGame();
		}
	}
	else
	{
		Mario->Update(deltaTime);
		BulletBill->Update(deltaTime);
		cEntityManager::Instance()->UpdateEntities(deltaTime);

		// INFO: Given that Bullet Bill collides with the player the player will die
		if (cCollisionManager::Instance()->ObjectCollision(Mario->GetBoxCollider()->GetRect(), BulletBill->GetBoxCollider()->GetRect()))
			Mario->SetIsDead(true);

		// INFO: Goes through all the entities and checks whether they have collided with mario
		for (int i = 0; i < entities.size(); i++)
		{
			if (cCollisionManager::Instance()->ObjectCollision(Mario->GetBoxCollider()->GetRect(), entities[i]->GetBoxCollider()->GetRect()) && !entities[i]->GetIsDead())
			{
				// INFO: If mario isn't grounded (jumping) and a collision occurs the goomba dies, otherwise mario dies
				if (!Mario->GetIsGrounded() && Mario->GetCenterPoint()->m_y < entities[i]->GetCenterPoint()->m_y)
				{
					if (!Mario->GetSquishedGoomba())
					{
						Mario->SetSquishedGoomba(true);
						cAudioManager::Instance()->PlayAudio(sGlobalStrings::Mario_GoombaStomp_SFX);
					}
					entities[i]->SetIsDead(true);
				}
				else
					Mario->SetIsDead(true);
			}
		}

		for (int i = 0; i < pickups.size(); i++)
		{
			if (cCollisionManager::Instance()->ObjectCollision(Mario->GetBoxCollider()->GetRect(), pickups[i]->GetBoxCollider()->GetRect()) && !pickups[i]->GetIsCollected())
			{
				pickups[i]->SetIsCollected(true);
				Mario->PickupEffect(pickups[i]->GetPickupType());
				cAudioManager::Instance()->PlayAudio(sGlobalStrings::Coin_SFX);

				std::string temp = "Score: " + std::to_string(Mario->GetScore());
				ScoreCounter->ChangeText(temp);
			}
		}

		cCamera::Instance()->Update(deltaTime);
	}
}

void cGame::Draw()
{
	SDL_RenderClear(m_renderer);

	cAssetManager::Instance()->Draw(sGlobalStrings::Background, 0, -100, 1024, 768, 0.1f);
	cAssetManager::Instance()->Draw(sGlobalStrings::Background, 1024, -100, 1024, 768, 0.1f);

	cMap::Instance()->DrawMap();
	cEntityManager::Instance()->DrawEntities();

	Mario->Draw();
	BulletBill->Draw();
	ScoreCounter->Draw();

	SDL_RenderPresent(m_renderer);
}

void cGame::Clean()
{	
	if (Mario != nullptr)
	{
		Mario->Clean();
		delete Mario;
		Mario = nullptr;
	}

	if (BulletBill != nullptr)
	{
		BulletBill->Clean();
		delete BulletBill;
		BulletBill = nullptr;
	}

	if (ScoreCounter != nullptr)
	{
		ScoreCounter->Clean();
		delete ScoreCounter;
		ScoreCounter = nullptr;
	}

	cAssetManager::Instance()->Clean();
	cAudioManager::Instance()->Clean();
	cCamera::Instance()->Clean();
	cMap::Instance()->Clean();
	cCollisionManager::Instance()->Clean();
	cEntityManager::Instance()->Clean();
	cInputManager::Instance()->Clean();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	TTF_Quit();

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_Quit();

	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

void cGame::ResetGame() 
{
	m_resetTime = static_cast<float>(SDL_GetTicks());

	m_bonusScore = 0;

	Mario->Reset();
	BulletBill->Reset();
	ScoreCounter->ChangeText("Score: 0");
	ScoreCounter->ChangeLabelPos(0, 0);

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Reset();
	}

	for (int i = 0; i < pickups.size(); i++)
	{
		pickups[i]->Reset();
	}
}
