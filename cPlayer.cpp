#include "cAssetManager.h"
#include "cCamera.h"
#include "cCollisionManager.h"
#include "cGame.h"
#include "cInputManager.h"
#include "cTextureStrings.h"
#include "cVector2.h"

#include "SDL.h"

#include "cPlayer.h"

cPlayer::cPlayer(sEssentials* required) : cCharacter(required)
{
	m_bIsGrounded = false;
	m_bIsJumping = false;

	m_jumpTime = 0.0f;
	m_jumpForce = 20.0f;

	m_rb2D = new cRigidbody();
	m_rb2D->SetGravity(BASE_GRAVITY * 0.75f);

	// INFO: Idle Animation
	m_animator->SetAnimation(cTextureStrings::Mario_Idle, 0, 10, 100, 2);
}

void cPlayer::Update(float deltaTime)
{
	Move(deltaTime);
	Jump(deltaTime);

	m_rb2D->Update(deltaTime);

	m_previousPosition->m_x = m_position->m_x;
	m_position->TranslateX(m_rb2D->GetPosition().m_x);
	m_boxCollider->Update(m_position->m_x, m_position->m_y, m_width * 2.0f, m_height * 1.9f);

	if (cCollisionManager::Instance()->MapCollision(m_boxCollider->GetBoxCollider()))
		m_position->m_x = m_previousPosition->m_x;


	m_previousPosition->m_y = m_position->m_y;
	m_position->TranslateY(m_rb2D->GetPosition().m_y);
	m_boxCollider->Update(m_position->m_x, m_position->m_y, m_width * 2.0f, m_height * 1.9f);


	if (cCollisionManager::Instance()->MapCollision(m_boxCollider->GetBoxCollider()))
	{
		m_bIsGrounded = true;
		m_position->m_y = m_previousPosition->m_y;
	}
	else
		m_bIsGrounded = false;
	
	
	std::cout << m_position->m_y << std::endl;

	m_centerPoint->m_x = m_position->m_x + m_width / 2.0f;
	m_centerPoint->m_y = m_position->m_y + m_height / 2.0f;

	m_animator->Update();
}

void cPlayer::Draw()
{
	m_animator->Draw(int(m_position->m_x), int(m_position->m_y), m_width, m_height);

	m_boxCollider->DrawBoxCollider();
}

void cPlayer::Clean()
{
}

void cPlayer::Move(float deltaTime)
{
	m_rb2D->CancelForceX();
	m_animator->SetAnimation(cTextureStrings::Mario_Idle, 0, 10, 100, 2, m_flip);

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_A))
	{
		m_flip = SDL_FLIP_HORIZONTAL;

		m_rb2D->AddForceX(-5, deltaTime);
		m_animator->SetAnimation(cTextureStrings::Mario_Run, 0, 12, 50, 2, m_flip);
	}

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_D))
	{
		m_flip = SDL_FLIP_NONE;

		m_rb2D->AddForceX(5, deltaTime);
		m_animator->SetAnimation(cTextureStrings::Mario_Run, 0, 12, 50, 2);
	}
}

void cPlayer::Jump(float deltaTime)
{
	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_SPACE) && m_bIsGrounded)
	{
		m_bIsGrounded = false;
		m_bIsJumping = true;
		m_rb2D->AddForceY(-m_jumpForce, deltaTime, ForceMode::Impulse);
	}

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_SPACE) && m_bIsJumping && m_jumpTime < JUMP_INTERVAL)
	{
		m_jumpTime += deltaTime;
		m_rb2D->AddForceY(-m_jumpForce, deltaTime, ForceMode::Impulse);
	}
	else
	{
		m_bIsJumping = false;
		m_jumpTime = 0.0f;
		m_rb2D->CancelForceY();
	}
}
