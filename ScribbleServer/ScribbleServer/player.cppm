module;
import <string>;
import <vector>;
export import score;
export import user;
export module player;



namespace ScribbleServer {
	export class Player : public User
	{
	public:
		Player();
		Player(const std::string& username, const std::string& password);

		void SetCanDraw(bool canDraw);
		void SetScore(uint16_t time);
		void SetScore(const std::vector<uint16_t>& times);
		void SetGuessedCorrectly(bool guessedCorrectly);
		void SetHasGuessed(bool hasGuessed);
		void SetWordLastGuessed(const std::string& wordLastGuessed);

		bool GetCanDraw() const;
		Score GetScore() const;
		bool GetGuessedCorrectly() const;
		bool GetHasGuessed() const;
		std::string GetWordLastGuessed() const;



	private:
		bool m_canDraw;
		bool m_guessedCorrectly;
		bool m_hasGuessed;
		uint16_t m_timeGuessedCorrectly;
		std::string m_wordLastGuessed;
		Score m_score;
	};
}

