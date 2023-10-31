module;
import <vector>;
import <cstdint>;
export module score;

namespace Scribble {
	export class Score {
	public:
		Score();
		void CalculateScoreGuesser(uint16_t);
		void CalculateScorePainter();
	private:
		int16_t m_score;
		static std::vector<int16_t> m_times;
		static const uint16_t kBONUS_THRESHHOLD = 30;
		static const uint16_t kMAX_ROUND_LENGTH = 60;
		static const uint16_t kMAX_POINTS = 100;
		uint16_t ScoreFormula(uint16_t);
	};
}