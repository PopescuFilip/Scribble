#include "Round.h"

Round::Round():m_word("")
{
}

float Round::GetInterval(const Word word, uint16_t duration)
{
	return m_duration / (word.GetWordSize() / 2);
}

Round::~Round()
{
}
