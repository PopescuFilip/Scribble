import round;
import word;

using namespace ScribbleServer;


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

Word Round::GetWord() const
{
	return m_word;
}

uint16_t Round::GetDuration()
{
	return m_duration;
}

void Round::SetWord(std::ifstream& file)
{
	m_word.SetWord( file);
}

void Round::RevealCharacter()
{
	m_word.RevealRandomCharacter();
}

Round::~Round()
{
}