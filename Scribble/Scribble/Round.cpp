import round;
import word;
using Scribble::Round;


Round::Round()
{
}

Round::Round(const Word& word) :m_word{ word }
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

void Scribble::Round::SetWord(std::ifstream& file)
{
	m_word.setWord( file);
}

Round::~Round()
{
}