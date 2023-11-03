#include <random>
import word;

using Scribble::Word;


Scribble::Word::Word():m_word{""}
{
}

Scribble::Word::Word(const std::string& word):m_word{word}
{
}

size_t Word::GetWordSize() const
{
    size_t length = m_word.size();
    return length;
}

std::string& Word::GetVisibleCharacters() const
{
    size_t length = m_word.size();
    std::string visibleCharacters = m_word;
    for (int i = 0; i < length; ++i) {
        if (revealedCharacters.find(i) == revealedCharacters.end())
        {
            visibleCharacters[i] = '_';
        }
    }
    return visibleCharacters;
}

void Word::revealRandomCharacter()
{
    size_t length = m_word.size();
    int randomIndex;
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> distribution(0, length - 1);

    do {
        randomIndex = distribution(engine);
    } while (revealedCharacters.find(randomIndex) != revealedCharacters.end());

    revealedCharacters.insert(randomIndex);
}

std::string Word::getEmptyWord() const
{
    size_t length = m_word.size();

    std::string emptyWord(length, '_');

    return emptyWord;
}


void Word::setWord(std::ifstream& file)
{
    if (!file.is_open()) {
        throw std::exception("Error file!\n");
        return;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<size_t> distribution(0, fileSize - 1);
    size_t randomPosition = distribution(engine);

    file.seekg(randomPosition);
    file >> m_word;

    revealedCharacters.clear();
}

