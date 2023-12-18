import timer;

using ScribbleServer::Timer;

Timer::Timer(const uint16_t& duration):
	m_duration{duration},
	m_isActive{false}
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
