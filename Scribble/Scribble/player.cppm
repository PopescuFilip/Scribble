module;
import <string>;
export import score;
export import user;
export module player;


namespace Scribble {
	export class Player : public User
	{
	public:
		Player();
		Player(const std::string& username, const std::string& password);
		std::string GetWordLastGuessed();
		bool GetCanDraw();
		Score GetScore();
		bool GetGuessedCorrectly();
		void SetWordLastGuessed(const std::string& wordLastGuessed);
		void SetCanDraw(bool canDraw);
		void SetScore(const Score& score);
		void SetGuessedCorrectly(bool guessedCorrectly);
	private:
		std::string m_wordLastGuessed;
		bool m_canDraw;
		Score m_score;
		bool m_guessedCorrectly;
	};
}

