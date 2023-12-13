#include <random>
import word;

using ScribbleServer::Word;


Word::Word():
    m_wordId{-1},
    m_word{""}
{
}

Word::Word(const std::string& word):
    m_wordId{-1},
    m_word{word}
{
}


size_t Word::GetWordSize() const
{
    return m_word.size();
}


std::string Word::GetVisibleCharacters() const
{
    size_t length = m_word.size();
    std::string visibleCharacters = m_word;
    for (int i = 0; i < length; ++i) {
        if (m_revealedCharacters.find(i) == m_revealedCharacters.end() && m_word[i] != ' ')
        {
            visibleCharacters[i] = '_';
        }
    }
    return visibleCharacters;
}

void Word::RevealRandomCharacter()
{
    size_t length = m_word.size();
    int randomIndex;
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> distribution(0, length - 1);

    do {
        randomIndex = distribution(engine);
    } while (m_revealedCharacters.find(randomIndex) != m_revealedCharacters.end() or m_word[randomIndex]==' ');

    m_revealedCharacters.insert(randomIndex);
}

bool ScribbleServer::Word::isRevealed() const
{
    uint16_t nonSpaceCharacters = GetNoOfCharacters();
    return (m_revealedCharacters.size() == nonSpaceCharacters);
}

bool ScribbleServer::Word::operator==(const std::string& word) const
{
    return m_word == word;
}

std::string Word::GetEmptyWord() const
{
    size_t length = m_word.size();

    std::string emptyWord(length, '_');

    return emptyWord;
}

uint16_t ScribbleServer::Word::GetNoOfCharacters() const
{
    uint16_t count = 0;
    for (char ch : m_word)
    {
        if (!std::isspace(static_cast<unsigned char>(ch)))
        {
            count++;
        }
    }
    return count;
}

int Word::GetWordId() const
{
    return m_wordId;
}

void Word::SetWordId(int wordId)
{
    m_wordId = wordId;
}

std::string Word::GetWord() const
{
    return m_word;
}

void Word::SetWord(const std::string& word)
{
    m_word = word;
    m_revealedCharacters.clear();
}


