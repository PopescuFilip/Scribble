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
        if (m_revealedCharacters.find(i) == m_revealedCharacters.end())
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
    } while (m_revealedCharacters.find(randomIndex) != m_revealedCharacters.end());

    m_revealedCharacters.insert(randomIndex);
}

std::string Word::GetEmptyWord() const
{
    size_t length = m_word.size();

    std::string emptyWord(length, '_');

    return emptyWord;
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


