#include "cAssetManager.h"
#include "cInputManager.h"
#include "cTextureStrings.h"

#include "SDL.h"

#include "cPlayer.h"

cPlayer::cPlayer(sEssentials* required) : cCharacter(required)
{
	m_rb2D = new cRigidbody();

	// INFO: Idle Animation
	m_animator->SetAnimation(cTextureStrings::Mario_Idle, 0, 10, 100, 2);
}

void cPlayer::Update(float deltaTime)
{
	m_rb2D->CancelForce();
	m_animator->SetAnimation(cTextureStrings::Mario_Idle, 0, 10, 100, 2, m_flip);

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_A)) 
	{
		m_flip = SDL_FLIP_HORIZONTAL;

		m_rb2D->AddForceX(-15, 0.5);
		m_animator->SetAnimation(cTextureStrings::Mario_Run, 0, 12, 50, 2, m_flip);
	}

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_D))
	{
		m_flip = SDL_FLIP_NONE;

		m_rb2D->AddForceX(15, 0.5);
		m_animator->SetAnimation(cTextureStrings::Mario_Run, 0, 12, 50, 2);
	}

	m_rb2D->Update(0.5);

	//m_position->Translate(m_rb2D->GetPosition());
	m_position->TranslateX(m_rb2D->GetPosition().m_x);

	m_animator->Update();
}

void cPlayer::Draw()
{
	m_animator->Draw(int(m_position->m_x), int(m_position->m_y), m_width, m_height);
}

void cPlayer::Clean()
{
}
