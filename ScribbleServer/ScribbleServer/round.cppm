module;
import <fstream>;
import <string>;
import <chrono>;
export import word;
export module round;

namespace ScribbleServer {
	export class Round {
	public:
		Round();
		Round(const Word& word); 
		float GetInterval() const;
		Word GetWord() const;
		uint16_t GetDuration();
		void SetWord(const std::string& word);
		void RevealCharacter();
		void Start();
		uint16_t GetElapsedTime();
		~Round();
	private:
		Word m_word;
		std::chrono::steady_clock::time_point m_startTime;
		static const uint16_t m_duration = 60;
	};
}