module;
import <string>;
export import score;
export module player;

namespace Scribble {
	export class Player
	{
	public:
		Player();
		Player(const std::string& username, const std::string& wordLastGuessed, bool canDraw, const Score& score);
		std::string GetUsername();
		std::string GetWordLastGuessed();
		bool GetCanDraw();
		Score GetScore();
		bool GetGuessedCorrectly();
		void SetUsername(const std::string& username);
		void SetWordLastGuessed(const std::string& wordLastGuessed);
		void SetCanDraw(bool canDraw);
		void SetScore(const Score& score);
		void SetGuessedCorrectly(bool guessedCorrectly);
	private:
		std::string m_username;
		std::string m_wordLastGuessed;
		bool m_canDraw;
		Score m_score;
		bool m_guessedCorrectly;
	};
}

