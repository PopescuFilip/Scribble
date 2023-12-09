module;
import <vector>;
import <string>;
import <cstdint>;
export module score;

namespace ScribbleServer {
	export class Score {
	public:
		Score();

		int GetScoreId() const;
		int GetUserId() const;
		uint16_t GetScore() const;

		void SetScoreId(const int& scoreId);
		void SetUserId(const int& username);
		void SetScore(const uint16_t& score);
		
	
		void CalculateScoreGuesser(uint16_t);
		void CalculateScorePainter(const std::vector<uint16_t>& times);
	private:
		uint16_t ScoreFormula(uint16_t);
	private:
		int m_scoreId;
		int m_username;
		int16_t m_score;

		static const uint16_t kBONUS_THRESHHOLD = 30;
		static const uint16_t kMAX_ROUND_LENGTH = 60;
		static const uint16_t kMAX_POINTS = 100;
	};
}