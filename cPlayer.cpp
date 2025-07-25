#include "cAssetManager.h"
#include "cAudioManager.h"
#include "cCamera.h"
#include "cCollisionManager.h"
#include "cGame.h"
#include "cInputManager.h"
#include "sGlobalStrings.h"
#include "cVector2.h"

#include "SDL.h"
#include "SDL_mixer.h"

#include "cPlayer.h"

#include "MemoryLeakDetector.h"

cPlayer::cPlayer(sEssentials* required) : cCharacter(required)
{
	m_bIsGrounded = false;
	m_bIsJumping = false;
	m_bSquishedGoomba = false;
	m_bJumpSFXPlayed = false;

	m_jumpTime = 0.0f;
	m_jumpForce = 25.0f;

	m_stompedTime = 0.0f;
	m_stompForce = 20.0f;

	m_deathTime = 0.0f;

	m_score = 0;

	m_movementSpeed = 7.5f;

	m_rb2D->SetGravity(BASE_GRAVITY * 0.75f);

	m_characterType = CharacterType::Player;

	// INFO: Idle Animation
	m_animator->SetAnimation(sGlobalStrings::Mario_Idle, 0, 10, 100, 2);
}

void cPlayer::Update(float deltaTime)
{
	// INFO: Ensures the following only happen once
	if (m_bIsDead && m_animator->GetCurrentAnimation() != sGlobalStrings::Mario_Death) 
	{
		m_rb2D->CancelForceX();

		if (m_rb2D->GetVelocity().m_y < 0)
			m_rb2D->CancelForceY();

		m_width = 32;
		m_height = 33;
		m_animator->SetAnimation(sGlobalStrings::Mario_Death, 0, 10, 85, 2, m_flip, true);
		cAudioManager::Instance()->PlayAudio(sGlobalStrings::Mario_Death_SFX);
	}

	// INFO: Custom death timer
	if (m_bIsDead)
	{
		m_deathTime += deltaTime;

		if (m_deathTime > DEATH_INTERVAL)
		{
			m_deathTime = 0.0f;
			cGame::Instance()->ResetGame();
		}
	}

	// INFO: Reset for when mario falls through the holes
	if (m_position->m_y > 600)
		cGame::Instance()->ResetGame();

	// INFO: Allows movement when player isn't dead
	if (!m_bIsDead)
	{
		Move(deltaTime);

		if (!m_bSquishedGoomba)
			Jump(deltaTime);
		else 
		{
			m_stompedTime += deltaTime;

			// INFO: Launches the player upwards when goomba has been stomped on
			if (m_stompedTime < STOMP_INTERVAL)
			{
				m_rb2D->AddForceY(UP * m_stompForce, deltaTime, ForceMode::Impulse);
				m_rb2D->SetGravity(BASE_GRAVITY * 0.75f);

				m_animator->SetAnimation(sGlobalStrings::Mario_Jump, 0, 2, 100, 2, m_flip);
			}
			else
			{
				m_bSquishedGoomba = false;
				m_stompedTime = 0.0f;
				m_rb2D->SetGravity(BASE_GRAVITY);

				if (!m_bIsGrounded)
					m_animator->SetAnimation(sGlobalStrings::Mario_Fall, 0, 2, 100, 2, m_flip);
			}
		}
	}

	m_rb2D->Update(deltaTime);

	m_previousPosition->m_x = m_position->m_x;
	m_position->TranslateX(m_rb2D->GetPosition().m_x);
	m_boxCollider->UpdateCollider(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), static_cast<int>(m_width * 2.0f), static_cast<int>(m_height * 1.95f));

	if (cCollisionManager::Instance()->MapCollision(m_boxCollider->GetRect()))
		m_position->m_x = m_previousPosition->m_x;

	// INFO: Left Border Blocks Player From Leaving the Map
	if (cCamera::Instance()->GetPosition().m_x > m_position->m_x)
		m_position->m_x = cCamera::Instance()->GetPosition().m_x;

	// INFO: Right Border Blocks Player From Leaving the Map
	if (cCamera::Instance()->GetPosition().m_x + cCamera::Instance()->GetCameraView().w - m_width * 2 < m_position->m_x)
		m_position->m_x = cCamera::Instance()->GetPosition().m_x + cCamera::Instance()->GetCameraView().w - m_width * 2;


	m_previousPosition->m_y = m_position->m_y;
	m_position->TranslateY(m_rb2D->GetPosition().m_y);
	m_boxCollider->UpdateCollider(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), static_cast<int>(m_width * 2.0f), static_cast<int>(m_height * 1.95f));


	if (cCollisionManager::Instance()->MapCollision(m_boxCollider->GetRect()))
	{
		if (m_rb2D->GetVelocity().m_y >= 0)
		{
			m_bIsGrounded = true;
			m_bJumpSFXPlayed = false;
		}

		m_rb2D->CancelForceY();
		m_rb2D->SetGravity(BASE_GRAVITY);

		m_position->m_y = m_previousPosition->m_y;
	}
	else
		m_bIsGrounded = false;

	// INFO: Used by camera to track camera target
	m_centerPoint->m_x = m_position->m_x + m_width / 2.0f;
	m_centerPoint->m_y = m_position->m_y + m_height / 2.0f;

	m_animator->Update();
}

void cPlayer::Draw()
{
	m_animator->Draw(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), m_width, m_height);

	//m_boxCollider->DrawBoxCollider();
}

void cPlayer::Move(float deltaTime)
{
	m_rb2D->CancelForceX();
	m_animator->SetAnimation(sGlobalStrings::Mario_Idle, 0, 10, 100, 2, m_flip);

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_A))
	{
		m_flip = SDL_FLIP_HORIZONTAL;

		m_rb2D->AddForceX(LEFT * m_movementSpeed, deltaTime);
		m_animator->SetAnimation(sGlobalStrings::Mario_Run, 0, 12, 50, 2, m_flip);
	}

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_D))
	{
		m_flip = SDL_FLIP_NONE;

		m_rb2D->AddForceX(RIGHT * m_movementSpeed, deltaTime);
		m_animator->SetAnimation(sGlobalStrings::Mario_Run, 0, 12, 50, 2);
	}
}

void cPlayer::Jump(float deltaTime)
{
	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_SPACE) && m_bIsGrounded && !m_bJumpSFXPlayed)
	{
		cAudioManager::Instance()->PlayAudio(sGlobalStrings::Mario_Jump_SFX);
		m_bJumpSFXPlayed = true;
	}

	// INFO: Variable jump height, if released prematurely the player will lose all upward velocity and start falling down
	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_SPACE) && m_bIsGrounded)
	{
		m_bIsGrounded = false;
		m_bIsJumping = true;
		m_rb2D->AddForceY(UP * m_jumpForce, deltaTime, ForceMode::Acceleration);
		m_rb2D->SetGravity(BASE_GRAVITY * 0.75f);
	}

	if (cInputManager::Instance()->GetKey(SDL_SCANCODE_SPACE) && m_bIsJumping && m_jumpTime < JUMP_INTERVAL)
	{
		m_jumpTime += deltaTime;
		m_rb2D->AddForceY(UP * m_jumpForce, deltaTime, ForceMode::Acceleration);
		m_animator->SetAnimation(sGlobalStrings::Mario_Jump, 0, 2, 100, 2, m_flip);
	}
	else
	{
		m_bIsJumping = false;
		m_jumpTime = 0.0f;
		m_rb2D->CancelForceY();
		m_rb2D->SetGravity(BASE_GRAVITY);

		if (!m_bIsGrounded)
			m_animator->SetAnimation(sGlobalStrings::Mario_Fall, 0, 2, 100, 2, m_flip);
	}
}

void cPlayer::Reset()
{
	m_position->m_x = m_startingPosition->m_x;
	m_position->m_y = m_startingPosition->m_y;

	m_bIsDead = false;

	m_bIsJumping = false;
	m_jumpTime = 0.0f;

	m_score = 0;

	m_flip = SDL_FLIP_NONE;
	cCamera::Instance()->Reset();

	m_width = 18;
	m_height = 33;

	m_animator->SetAnimation(sGlobalStrings::Mario_Idle, 0, 10, 100, 2);
}

void cPlayer::PickupEffect(PickupType pickupType)
{
	switch (pickupType)
	{
	case PickupType::None:
		break;
	case PickupType::Coin:
		m_score += 100;
		break;
	default:
		break;
	}
}
