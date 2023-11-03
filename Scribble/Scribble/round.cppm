module;
import <fstream>;
import <string>;
export import word;
export module round;

namespace Scribble {
	export class Round {
	public:
		Round();
		Round(const Word& word); 
		float GetInterval() const;
		Word GetWord() const;
		void SetWord(std::ifstream& file);
		~Round();
	private:
		Word m_word;
		static const uint16_t m_duration = 60;
	};
}