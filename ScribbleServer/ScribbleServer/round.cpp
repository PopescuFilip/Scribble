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

void Round::SetWord(const std::string& word)
{
	m_word.SetWord(word);
}

void Round::RevealCharacter()
{
	m_word.RevealRandomCharacter();
}

void Round::Start()
{
	m_startTime= std::chrono::high_resolution_clock::now();
}

uint16_t ScribbleServer::Round::GetElapsedTime()
{
	auto currentTime= std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime).count();

	return duration;
}

Round::~Round()
{
}