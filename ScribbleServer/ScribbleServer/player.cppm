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

		bool GetCanDraw();
		Score GetScore();
		bool GetGuessedCorrectly();

		void SetCanDraw(bool canDraw);
		void SetScore(uint16_t time);
		void SetScore(const std::vector<uint16_t>& times);
		void SetGuessedCorrectly(bool guessedCorrectly);
	private:
		bool m_canDraw;
		bool m_guessedCorrectly;
		uint16_t m_timeGuessedCorrectly;
		Score m_score;
	};
}

