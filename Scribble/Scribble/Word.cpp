module word;

using Scribble::Word;

size_t Word::GetWordSize() const
{
    size_t length = word.size();
    return length;
}

std::string& Word::GetVisibleCharacters() const
{
    size_t length = word.size();
    std::string visibleCharacters = word;
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
    size_t length = word.size();
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
    size_t length = word.size();

    std::string emptyWord(length, '_'); 

    return emptyWord;
}
