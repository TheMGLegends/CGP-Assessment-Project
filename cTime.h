#pragma once

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 2.0f;

class cTime
{
public:
	cTime(const cTime&) = delete;
	inline static cTime* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cTime(); }

	void Update();
	inline float DeltaTime() const { return m_deltaTime; }

private:
	cTime();
	static cTime* m_Instance;

	float m_deltaTime;
	float m_previousFrameTime;
};