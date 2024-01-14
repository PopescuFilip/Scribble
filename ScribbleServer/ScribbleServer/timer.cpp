import timer;
//#include "timer.h"

using ScribbleServer::Timer;

Timer::Timer(const uint16_t& duration):
	m_duration{ duration },
	m_isActive{ false }
{
}

uint16_t ScribbleServer::Timer::GetDuration() const
{
	return m_duration;
}

bool ScribbleServer::Timer::IsActive() const
{
	return m_isActive;
}

uint16_t Timer::GetElapsedTime() const
{
	auto currentTime{ std::chrono::high_resolution_clock::now() };
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime).count();
	return duration;
}

bool Timer::ReachedThreshold() const
{
	return GetElapsedTime() >= m_duration;
}

void Timer::Start()
{
	m_startTime = std::chrono::high_resolution_clock::now();
	m_isActive = true;
}

void Timer::Stop()
{
	m_isActive = false;
}
