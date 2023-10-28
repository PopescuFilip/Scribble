module;
import <string>;
export import "Score.h";
export module player;

namespace Scribble {
	export class Player
	{
	private:
		std::string m_username;
		std::string m_wordLastGuessed;
		bool m_canDraw;
		Score m_score;
	};
}

