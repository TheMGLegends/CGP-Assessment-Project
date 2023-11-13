#include <iostream>
#include "cGame.h"

cGame::cGame() : m_window{ nullptr }, m_renderer{ nullptr }, m_isRunning{ false }, m_inputManager { cInputManager::GetInstance() }
{
}

cGame::~cGame()
{
}

bool cGame::Initialize(const char* windowTitle, int width, int height, int xPosition, int yPosition)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		// INFO: Window Creation
		m_window = SDL_CreateWindow(windowTitle, xPosition, yPosition, width, height, NULL);

		if (m_window == nullptr) 
		{
			std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		// INFO: Renderer Creation
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

		if (m_renderer == nullptr) 
		{
			std::cout << "Failed to create renderer. SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		// INFO: Enable the Game Loop
		m_isRunning = true;
	}
	else 
	{
		std::cout << "Failed to initialize SDL. SDL error: " << SDL_GetError() << std::endl;
		m_isRunning = false; // INFO: Security Measure
		return false;
	}
	return true;
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

	// INFO: Specific Player Keyboard Inputs
	if (m_inputManager->GetKey(SDL_SCANCODE_A)) 
	{
		std::cout << "A Pressed!" << std::endl;
	}

	if (m_inputManager->GetKey(SDL_SCANCODE_D))
	{
		std::cout << "D Pressed!" << std::endl;
	}

	if (m_inputManager->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		std::cout << "Spacebar Pressed!" << std::endl;
	}

	m_inputManager->Update();
}

void cGame::Update()
{
}

void cGame::Draw()
{
	SDL_RenderClear(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void cGame::Clean()
{
	m_inputManager->Clean();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool cGame::IsRunning()
{
	return m_isRunning;
}
