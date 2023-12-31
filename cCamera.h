#pragma once

#include "cTransform.h"
#include "cVector2.h"
#include "SDL.h"

class cCamera
{
public:
	cCamera(const cCamera&) = delete;
	inline static cCamera* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cCamera(); }

	void Update(float deltaTime);

	inline SDL_Rect GetCameraView() const { return m_cameraView; }
	inline cVector2 GetPosition() const { return m_position; }

	inline void SetTarget(cTransform* target) { m_target = target; }

private:
	cCamera();
	static cCamera* m_Instance;

	cVector2 m_position;
	cTransform* m_target;
	int m_levelWidth;

	SDL_Rect m_cameraView;
};

