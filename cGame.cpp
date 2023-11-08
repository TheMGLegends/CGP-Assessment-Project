#include <iostream>
#include "cGame.h"

cGame::cGame() : m_window{ nullptr }, m_renderer{ nullptr }, m_keyboardState{ nullptr }, m_isRunning{ false }
{
}

cGame::~cGame()
{
}

void cGame::Initialize(const char* windowTitle, int width, int height, int xPosition, int yPosition)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		// INFO: Window Creation
		m_window = SDL_CreateWindow(windowTitle, xPosition, yPosition, width, height, NULL);

		if (m_window == nullptr) 
		{
			std::cout << "Failed to create window. SDL error: " << SDL_GetError() << std::endl;
		}

		// INFO: Renderer Creation
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

		if (m_renderer == nullptr) 
		{
			std::cout << "Failed to create renderer. SDL error: " << SDL_GetError() << std::endl;
		}

		// INFO: Get the Keyboards State
		m_keyboardState = SDL_GetKeyboardState(NULL);

		// INFO: Enable the Game Loop
		m_isRunning = true;
	}
	else 
	{
		std::cout << "Failed to initialize SDL. SDL error: " << SDL_GetError() << std::endl;
		m_isRunning = false; // INFO: Security Measure
	}
}

void cGame::HandleEvents()
{
	// TEMPORARY CODE:
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

	if (m_keyboardState[SDL_SCANCODE_ESCAPE]) 
	{
		m_isRunning = false;
	}
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
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool cGame::IsRunning()
{
	return m_isRunning;
}