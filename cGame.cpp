#include <iostream>

#include "cAssetManager.h"
#include "cAudioManager.h"
#include "cBulletBill.h"
#include "cCamera.h"
#include "cCollisionManager.h"
#include "cEntityManager.h"
#include "cGoomba.h"
#include "cInputManager.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cPickups.h"
#include "sGlobalStrings.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "cGame.h"

#include "MemoryLeakDetector.h"

cPlayer* Mario = nullptr;
cBulletBill* BulletBill = nullptr;
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
		cAssetManager::Instance()->LoadFont(sGlobalStrings::PixelArt_Font, "Assets/Fonts/PixelArt_Font.ttf", 16);

		// INFO: Initialise Music and SFX
		cAudioManager::Instance()->LoadAudio(sGlobalStrings::GroundTheme_Music, "Assets/Audio/GroundTheme_Music.mp3", true);

		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Mario_Death_SFX, "Assets/Audio/Mario_Death_SFX.mp3");
		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Mario_GoombaStomp_SFX, "Assets/Audio/Mario_GoombaStomp_SFX.mp3");
		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Mario_Jump_SFX, "Assets/Audio/Mario_Jump_SFX.mp3");

		cAudioManager::Instance()->LoadAudio(sGlobalStrings::Coin_SFX, "Assets/Audio/Coin_SFX.mp3");

		// INFO: Load Entities
		Mario = new cPlayer(new sEssentials(25, 300, 18, 33, sGlobalStrings::Mario_Idle));
		BulletBill = new cBulletBill(new sEssentials(2950, 350, 16, 16, sGlobalStrings::BulletBill_Fly, SDL_FLIP_HORIZONTAL));

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
		cAudioManager::Instance()->SetSFXVolume(sGlobalStrings::Mario_Jump_SFX, 2);
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
	if (m_bLevelCompleted)
	{
		std::cout << "Won game!" << std::endl;
		m_bLevelCompleted = false;
		ResetGame();
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
	Mario->Reset();
	BulletBill->Reset();

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Reset();
	}

	for (int i = 0; i < pickups.size(); i++)
	{
		pickups[i]->Reset();
	}
}
