//#include "SDL_image.h"
//#include "cAssetManager.h"
//#include "cTime.h"
#include <iostream>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include "cGame.h"

// INFO: Temporary Testing:
//SDL_Texture* playerTexture;
//SDL_Rect destinationRect;

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

		// INFO: Initialise SDL_Image:
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;

		if (IMG_Init(flags) != flags)
		{
			std::cout << "Failed to initialise SDL_Image. SDL_Image error: " << IMG_GetError() << std::endl;
			return false;
		}

		// INFO: Initialise SDL_Mixer:
		flags = MIX_INIT_MP3;

		if (Mix_Init(flags) != flags)
		{
			std::cout << "Failed to initialise SDL_Mixer. SDL_Mixer error: " << Mix_GetError() << std::endl;
			return false;
		}

		// INFO: Initialise SDL_TTF:
		if (TTF_Init() < 0)
		{
			std::cout << "Failed to initialise SDL_TTF. SDL_TTF error: " << TTF_GetError() << std::endl;
			return false;
		}
	
		// INFO: Initial Window Background Colour:
		SDL_SetRenderDrawColor(m_renderer, 92, 148, 252, 255);
	
		// INFO: Enable the Game Loop
		m_isRunning = true;

		return true;
	}
	else 
	{
		std::cout << "Failed to initialize SDL. SDL error: " << SDL_GetError() << std::endl;
		m_isRunning = false; // INFO: Security Measure
		return false;
	}
	
	//// INFO: Temporary Testing:
	//playerTexture = cAssetManager::LoadTexture("Assets/testPlayer.png", m_renderer); Testing if push works with .gitignore
}

void cGame::HandleEvents()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) 
	{
		switch (sdlEvent.type) 
		{
			case SDL_QUIT:
				m_isRunning = false;
				break;
		}
	}
	//
	//// INFO: Specific Player Keyboard Inputs
	//if (m_inputManager->GetKey(SDL_SCANCODE_A)) 
	//{
	//	std::cout << "A Pressed!" << std::endl;
	//}
	//
	//if (m_inputManager->GetKey(SDL_SCANCODE_D))
	//{
	//	std::cout << "D Pressed!" << std::endl;
	//}
	//
	//if (m_inputManager->GetKeyDown(SDL_SCANCODE_SPACE))
	//{
	//	std::cout << "Spacebar Pressed!" << std::endl;
	//}
	//
	//if (m_inputManager->GetKeyUp(SDL_SCANCODE_S)) 
	//{
	//	std::cout << "S Pressed!" << std::endl;
	//}
	//
	//m_inputManager->Update();
}

void cGame::Update()
{
	//// INFO: Temporary Testing:
	//count++;
	//
	//destinationRect.h = 100;
	//destinationRect.w = 100;
	//destinationRect.x = count;
	//
	//std::cout << count << std::endl;
}

void cGame::Draw()
{
	SDL_RenderClear(m_renderer);

	//// INFO: Temporary Testing:
	//SDL_RenderCopy(m_renderer, playerTexture, NULL, &destinationRect);

	SDL_RenderPresent(m_renderer);
}

void cGame::Clean()
{
	//m_inputManager->Clean();
	
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

