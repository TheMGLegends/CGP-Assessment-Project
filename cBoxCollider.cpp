#include "cCamera.h"
#include "cGame.h"
#include "cVector2.h"

#include "cBoxCollider.h"

void cBoxCollider::Update(int x, int y, int w, int h)
{
	m_boxCollider.x = x;
	m_boxCollider.y = y;
	m_boxCollider.w = w;
	m_boxCollider.h = h;
}

void cBoxCollider::DrawBoxCollider()
{
	cVector2 cameraPos = cCamera::Instance()->GetPosition();
	m_boxCollider.x -= cameraPos.m_x;
	m_boxCollider.y -= cameraPos.m_y;

	SDL_SetRenderDrawColor(cGame::Instance()->GetRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(cGame::Instance()->GetRenderer(), &m_boxCollider);
}
