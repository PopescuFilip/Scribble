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

        int GetWordId() const;
        std::string GetWord() const;

        void SetWordId(int wordId);
        void SetWord(const std::string& word);
        
        size_t GetWordSize() const;
        std::string GetVisibleCharacters() const;
        std::string GetEmptyWord() const;

        void RevealRandomCharacter();
        
    private:
        int m_wordId;
        std::string m_word;

        std::set<int> m_revealedCharacters;

    };
}
