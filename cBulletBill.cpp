#include <stdlib.h>

#include "cAssetManager.h"
#include "cTextureStrings.h"

#include "cBulletBill.h"

cBulletBill::cBulletBill(sEssentials* required) : cCharacter(required)
{
	m_characterType = CharacterType::BulletBill;
}

void cBulletBill::Update(float deltaTime)
{
	// INFO: If the entity reaches the left-most side of the map:
	if (m_position->m_x < -50) 
		Reset();

	m_position->TranslateX(-5.0f);
	m_boxCollider->Update((int)m_position->m_x, (int)m_position->m_y, m_width * 2.0f, m_height * 2.0f);
}

void cBulletBill::Draw()
{
	cAssetManager::Instance()->Draw(cTextureStrings::BulletBill_Fly, (int)m_position->m_x, (int)m_position->m_y, m_width, m_height, 1.0f, 2, m_flip);

	m_boxCollider->DrawBoxCollider();
}

void cBulletBill::Clean()
{
}

void cBulletBill::Reset()
{
	m_position->m_x = m_startingPosition->m_x;
	m_position->m_y = 100 + rand() % 276; // INFO: Random Value between 100-375 (Inclusive)
}
