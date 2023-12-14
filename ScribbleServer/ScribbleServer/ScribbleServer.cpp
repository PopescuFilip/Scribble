#include <iostream>
import round;
#include "routing.h"

int main()
{
    using namespace ScribbleServer;
    GameStorage storage;
    if (!storage.Initialize())
    {
        std::cout << "Faild to initialize the database!";
        return -1;
    }

    Routing r;
    r.Run(storage);

    std::cout << "Hello World!\n";
    return 0;
}

