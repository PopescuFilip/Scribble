module;

import<iostream>;
import <string>;
import <set>;
import<random>;
import<fstream>;

export module word;

namespace Scribble
{
    export class Word
    {
    public:
        Word();
        Word(const std::string& word);

        size_t GetWordSize() const ;
        // functia returneaza dimensiunea cuvantului

        std::string& GetVisibleCharacters() const;

        /*functia returneaza caracterele vizibile si cele necunoscute reprezentate ca underscores, si verifica
        daca respectivul caracter a fost dezvaluit sau nu*/

        void revealRandomCharacter() ;
        /*Aceasta functie dezvaluie cate un caracter aleatoriu din cuvant si se verifica daca respectivul
        caracter nu a fost deja dezvaluit.*/
        std::string getEmptyWord() const;
        // returneaza un string de "_" de dimensiunea word ului

        void setWord(std::ifstream& file);

    private:
        std::string m_word;
        std::set<int> revealedCharacters;

    };
}
