module;
import <vector>;
import <string>;
import <cstdint>;
export module score;

namespace ScribbleServer {
	export class Score {
	public:
		Score();

		uint16_t GetScore() const;
		uint16_t GetScoreId() const;
		std::string GetUsername() const;

		void SetScore(const uint16_t& score);
		void SetScoreId(const uint16_t& scoreId);
		void SetUsername(const std::string& username);
		
	
		void CalculateScoreGuesser(uint16_t);
		void CalculateScorePainter(const std::vector<uint16_t>& times);
	private:
		uint16_t ScoreFormula(uint16_t);
	private:
		uint16_t m_scoreId;
		std::string m_username;
		int16_t m_score;

		static const uint16_t kBONUS_THRESHHOLD = 30;
		static const uint16_t kMAX_ROUND_LENGTH = 60;
		static const uint16_t kMAX_POINTS = 100;
	};
}