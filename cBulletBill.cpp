#include <stdlib.h>

#include "cAssetManager.h"
#include "sGlobalStrings.h"

#include "cBulletBill.h"

#include "MemoryLeakDetector.h"

cBulletBill::cBulletBill(sEssentials* required) : cCharacter(required)
{
	m_characterType = CharacterType::BulletBill;
	m_movementSpeed = 5.0f;
}

void cBulletBill::Update(float deltaTime)
{
	// INFO: If the entity reaches the left-most side of the map:
	if (m_position->m_x < -50) 
		Reset();

	m_position->TranslateX(LEFT * m_movementSpeed);
	m_boxCollider->UpdateCollider(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), static_cast<int>(m_width * 2.0f), static_cast<int>(m_height * 2.0f));
}

void cBulletBill::Draw()
{
	// INFO: Since BB only has one frame (No animations) we can just draw him normally
	cAssetManager::Instance()->Draw(sGlobalStrings::BulletBill_Fly, static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), m_width, m_height, 1.0f, 2, m_flip);

	m_boxCollider->DrawBoxCollider();
}

void cBulletBill::Reset()
{
	m_position->m_x = m_startingPosition->m_x;

	// INFO: Random Value between 100-375 (Inclusive) determines the y-position of bullet bill 
	m_position->m_y = static_cast<float>(100 + rand() % 276);
}
