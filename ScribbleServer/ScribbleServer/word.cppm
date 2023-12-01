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
        uint16_t GetWordId() const;
        void SetWordId(uint16_t wordId);
        const std::string& GetWord() const;
        void SetWord(const std::string& word);

    private:
        uint16_t m_wordId;
        std::string m_word;
        std::set<int> m_revealedCharacters;

    };
}
