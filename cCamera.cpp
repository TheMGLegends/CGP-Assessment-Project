#include "cMap.h"

#include "cCamera.h"

cCamera* cCamera::m_Instance = nullptr;

void cCamera::Update(float deltaTime)
{
	if (m_target != nullptr) 
	{
		m_cameraView.x = m_target->m_x - static_cast<float>(SCREEN_WIDTH) / 2;

		if (m_cameraView.x > (cMap::Instance()->GetLevelWidth() - m_cameraView.w))
			m_cameraView.x = (cMap::Instance()->GetLevelWidth() - m_cameraView.w);

		if (m_cameraView.x > m_position.m_x)
			m_position = cVector2(m_cameraView.x, m_position.m_y);
		else
			m_position = cVector2(m_position.m_x, m_cameraView.y);
	}
}

cCamera::cCamera()
{
	m_target = new cTransform();

	m_cameraView = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

