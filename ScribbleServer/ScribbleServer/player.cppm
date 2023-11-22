module;
import <string>;
export import score;
export import user;
export module player;



namespace ScribbleServer {
	export class Player : public User
	{
	public:
		Player();
		Player(const std::string& username, const std::string& password);

		bool GetCanDraw();
		Score GetScore();
		bool GetGuessedCorrectly();

		void SetCanDraw(bool canDraw);
		void SetScore(const Score& score);
		void SetGuessedCorrectly(bool guessedCorrectly);
	private:
		uint16_t m_playerId;
		std::string username;

		bool m_canDraw;
		bool m_guessedCorrectly;
		uint16_t m_timeGuessedCorrectly;
		Score m_score;
	};
}

