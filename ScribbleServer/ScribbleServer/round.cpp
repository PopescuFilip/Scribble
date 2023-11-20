import round;
import word;
using ScribbleServer::Round;


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

ScribbleServer::Word Round::GetWord() const
{
	return m_word;
}

void ScribbleServer::Round::SetWord(std::ifstream& file)
{
	m_word.setWord( file);
}

void ScribbleServer::Round::RevealCharacter()
{
	m_word.revealRandomCharacter();
}

uint16_t ScribbleServer::Round::GetDuration()
{
	return m_duration;
}

Round::~Round()
{
}