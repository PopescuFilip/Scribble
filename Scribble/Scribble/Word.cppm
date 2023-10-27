module;

import <string>;
import <random>;
import <set>;

export module wordModule;

namespace Scribble
{
    class Word
    {
    public:
        std::string word;
        std::set<int> revealedCharacters;

        Word(std::string word) {};

        std::string GetWordSize() const ;
        // functia returneaza dimensiunea cuvantului

        std::string GetVisibleCharacters() const;

        /*functia returneaza caracterele vizibile si cele necunoscute reprezentate ca underscores, si verifica
        daca respectivul caracter a fost dezvaluit sau nu*/

        void revealRandomCharacter() ;
        /*Aceasta functie dezvaluie cate un caracter aleatoriu din cuvant si se verifica daca respectivul
        caracter nu a fost deja dezvaluit.*/

    };
}
