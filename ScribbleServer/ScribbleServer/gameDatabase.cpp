#include "gameDatabase.h"
//#include <fstream>
#include <random>

using namespace ScribbleServer;
using namespace sqlite_orm;

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

void GameStorage::AddScore(const Score& score)
{
    m_db.insert(score);
}

bool GameStorage::AddUser(std::string username, std::string password)
{
    if (UsernameExists(username))
        return false;

    AddUser(User(username, password));
    return true;
}

bool GameStorage::CheckUser(const std::string& username, const std::string& password)
{
    auto count = m_db.count<User>(sql::where(sql::c(&User::GetUsername) == username and (sql::c(&User::GetPassword) == password)));
    return count != 0;
}

bool GameStorage::UsernameExists(const std::string& username)
{
    auto count = m_db.count<User>(sql::where(sql::c(&User::GetUsername) == username));
    return count != 0;
}

std::vector<Score> GameStorage::GetLast5Scores(const int& userId)
{
    auto userScores = m_db.get_all<Score>(sql::where(sql::c(&Score::GetUserId) == userId), order_by(&Score::GetScoreId).desc(), limit(5));
    return userScores;
}

void GameStorage::ClearUsers()
{
    m_db.remove_all<User>();
}

std::vector<User> GameStorage::GetUsers()
{
    return m_db.get_all<User>();
}

User GameStorage::GetUser(const int userId)
{
    return m_db.get<User>(userId);
}

int GameStorage::GetUserId(const std::string& username)
{
    auto userId = m_db.select(&User::GetUserId, sql::where(sql::c(&User::GetUsername) == username));

    return userId[0];
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
