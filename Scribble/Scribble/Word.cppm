module;

import <string>;
import <random>;
import <set>;

export module word;

namespace Scribble
{
    export class Word
    {
    public:
        std::string word;
        std::set<int> revealedCharacters;

        Word(std::string word) {};

        int GetWordSize() const ;
        // functia returneaza dimensiunea cuvantului

        std::string GetVisibleCharacters() const;

        /*functia returneaza caracterele vizibile si cele necunoscute reprezentate ca underscores, si verifica
        daca respectivul caracter a fost dezvaluit sau nu*/

        void revealRandomCharacter() ;
        /*Aceasta functie dezvaluie cate un caracter aleatoriu din cuvant si se verifica daca respectivul
        caracter nu a fost deja dezvaluit.*/

    };
}
