#include "cMap.h"

#include "cCamera.h"

#include "MemoryLeakDetector.h"

cCamera* cCamera::m_Instance = nullptr;

void cCamera::Update(float deltaTime)
{
	// INFO: So long as the camera has a target, its' x position is updated to match that of the targets x position
	if (m_target != nullptr) 
	{
		// INFO: Ensures the target stays in the middle of the display
		m_cameraView.x = static_cast<int>(m_target->m_x - static_cast<float>(SCREEN_WIDTH) / 2);

		// INFO: Prevents the camera from going any further than the width of the level
		if (m_cameraView.x > (cMap::Instance()->GetLevelWidth() - m_cameraView.w))
			m_cameraView.x = (cMap::Instance()->GetLevelWidth() - m_cameraView.w);

		// INFO: Prevents the camera from moving negatively on the x-axis to mimic the camera style that the original mario has
		if (m_cameraView.x > m_position.m_x)
			m_position = cVector2(static_cast<float>(m_cameraView.x), static_cast<float>(m_position.m_y));
		else
			m_position = cVector2(static_cast<float>(m_position.m_x), static_cast<float>(m_cameraView.y));
	}
}

void cCamera::Clean()
{
	if (m_Instance != nullptr) 
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

void cCamera::SetTarget(cTransform* target)
{
	if (m_target != nullptr)
	{
		delete m_target;
		m_target = nullptr;
	}

	m_target = target;
}

cCamera::cCamera()
{
	m_target = new cTransform();

	m_cameraView = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

