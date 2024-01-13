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

		void SetScore(uint16_t time);
		void SetScore(const std::vector<uint16_t>& times);

		Score GetScore() const;
		bool HasGuessedCorrectly() const;
		uint16_t GetTimeGuessed() const;

		void GuessWord(uint16_t time);
		void Reset();

	private:
		bool m_guessedCorrectly;
		uint16_t m_timeGuessed;
		Score m_score;
	};
}

