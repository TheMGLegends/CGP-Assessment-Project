#pragma once

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 0.75f;

class cTime
{
public:
	cTime(const cTime&) = delete;
	inline static cTime* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cTime(); }

	void Update();
	void Clean();
	inline float DeltaTime() const { return m_deltaTime; }

	inline float GetCurrentTime() const { return m_currentTime; }
	inline void SetResetTime() { m_resetTime = static_cast<float>(SDL_GetTicks()); }

private:
	cTime();
	static cTime* m_Instance;

	float m_deltaTime;
	float m_previousFrameTime;

	float m_currentTime;
	float m_resetTime;
};