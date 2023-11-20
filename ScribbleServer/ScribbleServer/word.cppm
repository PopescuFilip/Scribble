module;

import<iostream>;
import <string>;
import <set>;
import<random>;
import<fstream>;

export module word;

namespace ScribbleServer
{
    export class Word
    {
    public:
        Word();
        Word(const std::string& word);

        size_t GetWordSize() const;
        std::string& GetVisibleCharacters() const;
        void revealRandomCharacter();
        std::string getEmptyWord() const;
        void setWord(std::ifstream& file);

    private:
        std::string m_word;
        std::set<int> revealedCharacters;

    };
}
