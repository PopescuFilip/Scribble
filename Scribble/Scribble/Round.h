#pragma once
#include <iostream>
//#include "Word.h"


class Round
{
public:
	Round();
	//float GetInterval(const Word word, uint16_t duration);
	void GetWord(std::istream& file);
	~Round();

private:
	//Word m_word;
	static const uint8_t m_duration=60;
};

