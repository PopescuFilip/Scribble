module;
import <string>;
import <vector>;
export import score;
export import user;
export module player;



namespace ScribbleServer 
{
	export class Player : public User
	{
	public:
		Player(const User& user);

		void SetCanDraw(bool canDraw);
		void SetScore(uint16_t time);
		void SetScore(const std::vector<uint16_t>& times);
		void SetGuessedCorrectly(bool guessedCorrectly);
		void SetHasGuessed(bool hasGuessed);
		void SetWordLastGuessed(const std::string& wordLastGuessed);

		bool GetCanDraw() const;
		Score GetScore() const;
		bool HasGuessedCorrectly() const;
		bool HasGuessed() const;
		std::string GetWordLastGuessed() const;
		uint16_t GetTimeGuessed() const;

		void GuessWord(const std::string& word, uint16_t time);
		void Reset();

	private:
		bool m_canDraw;
		bool m_guessedCorrectly;
		bool m_hasGuessed;
		uint16_t m_timeGuessed;
		std::string m_wordLastGuessed;
		Score m_score;
	};
}

