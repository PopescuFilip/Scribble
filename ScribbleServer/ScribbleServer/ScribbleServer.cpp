#include <iostream>
#include "routing.h"

int main()
{
	 using namespace ScribbleServer;

    std::shared_ptr<GameStorage> storage = std::make_shared<GameStorage>();
    if (!storage->Initialize())
    {
        std::cout << "Faild to initialize the database!";
        return -1;
    }
    auto users{ storage->GetUsers() };
    std::cout << "users:\n";
    for (const auto& user : users)
    {
        std::cout << user.GetUserId() << " " << user.GetUsername() << " " << user.GetPassword() << "\n";
        /*auto scores{ storage->GetLast5Scores(user.GetUserId()) };
        for (const auto& score : scores)
        {
            std::cout << score.GetScoreId() << " " << score.GetScoreValue() << "\n";
        }*/
    }
    Routing r;
    r.Run(storage);

    std::cout << "Hello World!\n";
    return 0;
}

