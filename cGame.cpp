#include <iostream>

#include "cAssetManager.h"
#include "cBulletBill.h"
#include "cCamera.h"
#include "cCollisionManager.h"
#include "cGoomba.h"
#include "cInputManager.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cTextureStrings.h"

#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "cGame.h"

cPlayer* Mario = nullptr;
cBulletBill* BulletBill = nullptr;
cGoomba* Goomba = nullptr;

std::vector< std::vector<int> > lvl1 = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0},
{0,0,0,0,0,0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,4,0,0,0,4,0,0,0,4,0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,3,4,3,0,0,0,0,0,2,2,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,0,0,2,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

cGame* cGame::m_Instance = nullptr;

cGame::cGame()
{
	m_window = nullptr;
	m_renderer = nullptr;
	m_isRunning = false;
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

		// INFO: Initialise SDL_TTF
		if (TTF_Init() < 0)
		{
			std::cout << "Failed to initialise SDL_TTF. SDL_TTF error: " << TTF_GetError() << std::endl;
			return false;
		}
	
		// INFO: Initial Window Background Colour
		SDL_SetRenderDrawColor(m_renderer, 92, 148, 252, 255);
	
		// INFO: Enable the Game Loop
		m_isRunning = true;

		// INFO: Initialise Textures
		cAssetManager::Instance()->LoadTexture(cTextureStrings::Tilemap, "Assets/Tilemap.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(cTextureStrings::Background, "Assets/Background.png", m_renderer);

		cAssetManager::Instance()->LoadTexture(cTextureStrings::Mario_Idle, "Assets/Mario_Idle.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(cTextureStrings::Mario_Run, "Assets/Mario_Run.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(cTextureStrings::Mario_Jump, "Assets/Mario_Jump.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(cTextureStrings::Mario_Fall, "Assets/Mario_Fall.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(cTextureStrings::Mario_Death, "Assets/Mario_Death.png", m_renderer);

		cAssetManager::Instance()->LoadTexture(cTextureStrings::BulletBill_Fly, "Assets/BulletBill_Fly.png", m_renderer);

		cAssetManager::Instance()->LoadTexture(cTextureStrings::Goomba_Walk, "Assets/Goomba_Walk.png", m_renderer);
		cAssetManager::Instance()->LoadTexture(cTextureStrings::Goomba_Death, "Assets/Goomba_Death.png", m_renderer);

		// INFO: Load Entities
		Mario = new cPlayer(new sEssentials(25, 300, 18, 33, cTextureStrings::Mario_Idle));
		BulletBill = new cBulletBill(new sEssentials(2950, 350, 16, 16, cTextureStrings::BulletBill_Fly, SDL_FLIP_HORIZONTAL));
		Goomba = new cGoomba(new sEssentials(300, 325, 16, 16, cTextureStrings::Goomba_Walk));

		// INFO: Load Map
		cMap::Instance()->LoadMap(lvl1);

		// INFO: Set Camera Target
		cCamera::Instance()->SetTarget(Mario->GetCenterPoint());

		return true;
	}
	else 
	{
		std::cout << "Failed to initialize SDL. SDL error: " << SDL_GetError() << std::endl;
		m_isRunning = false; // INFO: Security Measure
		return false;
	}
}

void cGame::HandleEvents()
{
	cInputManager::Instance()->Update();
}

void cGame::Update(float deltaTime)
{
	Mario->Update(deltaTime);
	BulletBill->Update(deltaTime);
	Goomba->Update(deltaTime);

	if (cCollisionManager::Instance()->ObjectCollision(Mario->GetBoxCollider()->GetRect(), BulletBill->GetBoxCollider()->GetRect())) 
	{
		Mario->SetIsDead(true);
		BulletBill->Reset();
	}
	
	Mario->GetRigidBody()->GetVelocity().DisplayVector();

	if (cCollisionManager::Instance()->ObjectCollision(Mario->GetBoxCollider()->GetRect(), Goomba->GetBoxCollider()->GetRect()) && !Goomba->GetIsDead()) 
	{
		if (!Mario->GetIsGrounded())
		{
			Mario->SetSquishedGoomba(true);
			Goomba->SetIsDead(true);
		}
		else
		{
			Mario->SetIsDead(true);
			Goomba->Reset();
		}
	}


	cCamera::Instance()->Update(deltaTime);
}

void cGame::Draw()
{
	SDL_RenderClear(m_renderer);

	cAssetManager::Instance()->Draw(cTextureStrings::Background, 0, -100, 1024, 768, 0.1f);
	cAssetManager::Instance()->Draw(cTextureStrings::Background, 1024, -100, 1024, 768, 0.1f);
	cMap::Instance()->DrawMap();

	Goomba->Draw();
	Mario->Draw();
	BulletBill->Draw();

	SDL_RenderPresent(m_renderer);
}

void cGame::Clean()
{	
	cAssetManager::Instance()->Clean();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

