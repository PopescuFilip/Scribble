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

    auto users{ storage->GetUsers() };
    for (const User& user : users)
    {
        std::cout << user.GetUserId() << " " << user.GetUsername() << "\n";
        g.AddPlayer(user.GetUserId());
    }

    g.RunOneRound(0);
    
    

   /* Routing r;
    r.Run(storage);*/

    std::cout << "Hello World!\n";
    return 0;
}

