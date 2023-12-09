#include <iostream>
import round;
#include "gameDatabase.h"

int main()
{
    using namespace ScribbleServer;
    GameStorage storage;
    if (!storage.Initialize())
    {
        std::cout << "Faild to initialize the database!";
        return -1;
    }

    const auto& words = storage.GetWords();
    for (const auto& word : words)
    {
        std::cout << word.GetWord() << '\n';
    }

    std::cout << "Hello World!\n";
    return 0;
}

