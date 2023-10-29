module word;


using Scribble::Word;

int Word::GetWordSize() const
{
    size_t length = word.size();
    return length;
}

std::string Word::GetVisibleCharacters() const
{
    size_t length = word.size();
    std::string visibleword = word;
    for (int i = 0; i < length; ++i) {
        if (revealedCharacters.find(i) == revealedCharacters.end())
        {
            visibleword[i] = '_';
        }
    }
    return visibleword;
}