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

    User user{ "user", "password" };
    //storage.AddUser(user);

    const auto& users = storage.GetUsers();
    for (const auto& user : users)
    {
        std::cout << user.GetUserId() << " " << user.GetUsername() << " " << user.GetPassword() << std::endl;
    }

    std::cout << storage.CheckUser(user) << std::endl;
    std::cout << storage.CheckUser(User{ "username", "pass" }) << std::endl;

    /*const auto& words = storage.GetWords();
    int index = 0;
    for (const auto& word : words)
    {
        std::cout << index << " " << word.GetWord() << '\n';
        index++;
    }*/

    std::cout << "Hello World!\n";
    return 0;
}

