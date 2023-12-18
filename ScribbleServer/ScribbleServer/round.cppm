module;
import <fstream>;
import <string>;
import <chrono>;
//#include <chrono>
export import word;
export module round;

namespace ScribbleServer 
{
	export class Round 
	{
	public:
		Round();
		Round(const Word& word); 
		
		uint16_t GetInterval() const;
		Word GetWord() const;
		uint16_t GetDuration() const;

		void SetWord(const std::string& word);

		void RevealCharacter();
		void Start();
		uint16_t GetElapsedTime() const;

	private:
		Word m_word;
		std::chrono::steady_clock::time_point m_startTime;
		static const uint16_t m_duration = 60;
	};
}