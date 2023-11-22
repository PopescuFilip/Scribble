module;
import <fstream>;
import <string>;
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

		void SetWord(std::ifstream& file);

		void RevealCharacter();
		~Round();
	private:
		Word m_word;
		static const uint16_t m_duration = 60;
	};
}