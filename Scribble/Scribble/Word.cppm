module;

import<iostream>;
import <string>;
import <set>;
import<random>;

export module word;

namespace Scribble
{
    export class Word
    {
    public:
        Word() : word("")
        {
        }

        Word(const Word& other) : word(other.word)
        {
        }

        size_t GetWordSize() const ;
        // functia returneaza dimensiunea cuvantului

        std::string& GetVisibleCharacters() const;

        /*functia returneaza caracterele vizibile si cele necunoscute reprezentate ca underscores, si verifica
        daca respectivul caracter a fost dezvaluit sau nu*/

        void revealRandomCharacter() ;
        /*Aceasta functie dezvaluie cate un caracter aleatoriu din cuvant si se verifica daca respectivul
        caracter nu a fost deja dezvaluit.*/
    private:
        std::string word;
        std::set<int> revealedCharacters;

    };
}
