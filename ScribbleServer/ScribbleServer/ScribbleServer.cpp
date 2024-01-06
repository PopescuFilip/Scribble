#include <iostream>
#include "game.h"

int main()
{
    using namespace ScribbleServer;
    std::shared_ptr<GameStorage> storage = std::make_shared<GameStorage>();
    if (!storage->Initialize())
    {
        std::cout << "Faild to initialize the database!";
        return -1;
    }
    Game g{ storage };

   /* Routing r;
    r.Run(storage);*/

    std::cout << "Hello World!\n";
    return 0;
}

