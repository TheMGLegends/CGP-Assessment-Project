#include "cAssetManager.h"
#include "cTextureStrings.h"

#include "SDL.h"

#include "cPlayer.h"

cPlayer::cPlayer(sEssentials* required) : cCharacter(required)
{
	m_animator->SetAnimation(cTextureStrings::Mario_Run, 0, 5, 100);
	m_rb2D = new cRigidbody();
}

void cPlayer::Update(float deltaTime)
{
	m_rb2D->Update(0.5);

	m_position->Translate(m_rb2D->GetPosition());

	m_animator->Update();
}

void cPlayer::Draw()
{
	m_animator->Draw(int(m_position->m_x), int(m_position->m_y), 35, 27);
}

void cPlayer::Clean()
{
}
