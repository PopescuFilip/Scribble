import round;
import word;
using Scribble::Round;


Round::Round() :m_word("")
{
}

Round::Round(const Word& word) :m_word(word)
{
}

float Round::GetInterval() const
{
	return (m_duration / m_word.GetWordSize());
}

Scribble::Word Round::GetWord() const
{
	return m_word;
}

Round::~Round()
{
}