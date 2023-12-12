#include "gameDatabase.h"
//#include <fstream>
#include <random>

using namespace ScribbleServer;

bool GameStorage::Initialize()
{
    m_db.sync_schema();
    auto initWordsCount = m_db.count<Word>();

    if (!initWordsCount)
        PopulateStorage();

    auto wordsCount = m_db.count<Word>();

    return wordsCount != 0;
}

Word GameStorage::GetRandomWord()
{
    auto wordsCount = m_db.count<Word>();

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> distribution(0, wordsCount);

    auto randomId = distribution(engine);
    
    return m_db.get<Word>(randomId);
}

std::vector<Word> GameStorage::GetWords()
{
    return m_db.get_all<Word>();
}

void GameStorage::AddUser(const User& user)
{
    m_db.insert(user);
}

void GameStorage::AddUser(const std::string& user, const std::string& password)
{
    m_db.insert(User{ user, password });
}

void GameStorage::AddScore(const Score& score)
{
    m_db.insert(score);
}

bool GameStorage::CheckUser(const User& user)
{
    auto count = m_db.count<User>(sql::where(sql::c(&User::GetUsername) == user.GetUsername()));
    return count != 0;
}

std::vector<User> GameStorage::GetUsers()
{
    return m_db.get_all<User>();
}

void GameStorage::PopulateStorage()
{
    std::ifstream file(kWordFile);
    std::string wordFromFile;

    while (std::getline(file, wordFromFile))
    {
        m_db.insert(Word{ wordFromFile });
    }

    file.close();
}

AddToUserHandler::AddToUserHandler(GameStorage& storage)
    :m_db{ storage }
{
}

crow::response AddToUserHandler::operator()(const crow::request& req) const
{
    auto bodyArgs = parseUrlArgs(req.body);
    auto end = bodyArgs.end();
    auto usernameIter = bodyArgs.find("username");
    auto passwordIter = bodyArgs.find("password");
    if (usernameIter != end && passwordIter != end)
    {
        m_db.AddUser(usernameIter->second, passwordIter->second);
    }
    return crow::response(201); 
}
