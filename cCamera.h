#pragma once

#include "cGame.h"
#include "cTransform.h"
#include "cVector2.h"

#include "SDL.h"

class cCamera
{
public:
	cCamera(const cCamera&) = delete;
	inline static cCamera* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cCamera(); }

	void Update(float deltaTime);
	void Clean();

	inline SDL_Rect GetCameraView() const { return m_cameraView; }
	inline cVector2 GetPosition() const { return m_position; }

	inline void SetTarget(cTransform* target) { m_target = target; }
	inline void Reset() { m_position = cVector2::ZERO; m_cameraView.x = 0; m_cameraView.y = 0; }

private:
	cCamera();
	static cCamera* m_Instance;

	cVector2 m_position;
	cTransform* m_target;

	SDL_Rect m_cameraView;
};

