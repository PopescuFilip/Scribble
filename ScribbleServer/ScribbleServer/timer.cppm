export module timer;

import <chrono>;

namespace ScribbleServer
{
	export class Timer
	{
	public:
		Timer(const uint16_t& duration);

		uint16_t GetDuration() const;
		bool IsActive() const;
		uint16_t GetElapsedTime() const;
		bool ReachedThreshold() const;
		void Start();
		void Stop();

	private:
		std::chrono::steady_clock::time_point m_startTime;
		bool m_isActive;
		const uint16_t m_duration;
	};
}