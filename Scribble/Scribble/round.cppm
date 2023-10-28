module;
import <fstream>;
import <string>;
export import word;
export module round;

namespace Scribble {
	export class Round {
	public:
		Round();
		Round(const Word& word); //
		void SetWord(std::ifstream& file);  // cred ca putem sa l punem in word
		float GetInterval() const;
		Word GetWord() const;
		~Round();
	private:
		Word m_word;
		static const uint8_t m_duration = 60;
	};
}