﻿#include "TimerManager.h"

namespace gameframework
{
	void TimerManager::Timer::Start()
	{
		Reset();
		m_startTime = std::chrono::system_clock::now();
	}

	void TimerManager::Timer::Pause()
	{
		if (!IsRunning()) return;

		m_isRunning = false;

		MeasureElapsedTime();

		m_timeWhenStopped = m_elapsedTime;

		m_sysTimeWhenStopped = std::chrono::system_clock::now();
	}

	void TimerManager::Timer::Restart()
	{
		m_startTime += (std::chrono::system_clock::now() - m_sysTimeWhenStopped);

		m_isRunning = true;
	}

	void TimerManager::Timer::Reset()
	{
		m_elapsedTime = m_elapsedTime.zero();

		m_isRunning = true;
	}

	LONGLONG TimerManager::Timer::GetTime_sec()
	{
		if (!IsRunning())
		{
			return std::chrono::duration_cast<std::chrono::seconds>(m_timeWhenStopped).count();
		}

		MeasureElapsedTime();
		return std::chrono::duration_cast<std::chrono::seconds>(m_elapsedTime).count();
	}

	LONGLONG TimerManager::Timer::GetTime_msec()
	{
		if (!IsRunning())
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(m_timeWhenStopped).count();
		}

		MeasureElapsedTime();
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_elapsedTime).count();
	}

	LONGLONG TimerManager::Timer::GetTime_µsec()
	{
		if (!IsRunning())
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(m_timeWhenStopped).count();
		}

		MeasureElapsedTime();
		return std::chrono::duration_cast<std::chrono::microseconds>(m_elapsedTime).count();
	}

	void TimerManager::Timer::MeasureElapsedTime()
	{
		m_elapsedTime = std::chrono::system_clock::now() - m_startTime;
	}

	bool TimerManager::CanStartNextFrame()
	{
		LONGLONG currentFrameSyncTime_msec = m_timers[_T("FPS")]->GetTime_msec();

		if (currentFrameSyncTime_msec - m_prevFrameSyncTime_msec < 1000 / m_fPS) return false;

		//一フレームにかかった時間をdeltaTime_secのため取得する
		m_processTimeAtPrevFrame_msec = currentFrameSyncTime_msec - m_prevFrameSyncTime_msec;

		m_prevFrameSyncTime_msec = currentFrameSyncTime_msec;

		return true;
	}

	float TimerManager::DeltaTime_sec() const
	{
		float deltaTime_sec = static_cast<float>(m_processTimeAtPrevFrame_msec) / 1000.0f;

		return deltaTime_sec;
	}
}
