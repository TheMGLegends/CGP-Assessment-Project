#include "cCamera.h"
#include "cGame.h"
#include "cVector2.h"

#include "cBoxCollider.h"

void cBoxCollider::Update(int x, int y, int w, int h)
{
	m_rectCollider.x = x;
	m_rectCollider.y = y;
	m_rectCollider.w = w;
	m_rectCollider.h = h;
}

void cBoxCollider::DrawBoxCollider()
{
	cVector2 cameraPos = cCamera::Instance()->GetPosition();
	m_rectCollider.x -= cameraPos.m_x;
	m_rectCollider.y -= cameraPos.m_y;

	SDL_SetRenderDrawColor(cGame::Instance()->GetRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(cGame::Instance()->GetRenderer(), &m_rectCollider);
}
