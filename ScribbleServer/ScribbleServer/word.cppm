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
        std::string GetVisibleCharacters() const;
        void RevealRandomCharacter();
        std::string GetEmptyWord() const;
        void SetWord(std::ifstream& file);


    private:
        uint16_t m_wordId;
        std::string m_word;
        std::set<int> m_revealedCharacters;

    };
}
