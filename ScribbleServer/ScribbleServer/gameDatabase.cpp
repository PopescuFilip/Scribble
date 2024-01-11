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

    AddUser(username, password);
    return true;
}

bool GameStorage::CheckUser(const std::string& username, const std::string& password)
{
    auto count = m_db.count<User>(sql::where(sql::c(&User::GetUsername) == username) and (sql::c(&User::GetPassword) == password));
    return count != 0;
}

bool GameStorage::UsernameExists(const std::string& username)
{
    auto count = m_db.count<User>(sql::where(sql::c(&User::GetUsername) == username));
    return count != 0;
}

std::vector<Score> GameStorage::GetLast5Scores(const int& userId)
{
    auto allUserScores = m_db.get_all<Score>(
        sql::where(sql::c(&Score::GetUserId) == userId)
    ); //returneaza scorurile corespunzatoare unui utilizator

    int scoresToRetrieve = std::min(static_cast<int>(allUserScores.size()), 5); //afisare ultimele 5 scoruri in caz ca-s mai multe
    std::vector<Score> last5Scores(allUserScores.begin(), allUserScores.begin() + scoresToRetrieve); //creeaza vectorul cu ultimele 5 scoruri

    return last5Scores;
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
        //m_db.AddUser(usernameIter->second, passwordIter->second);
    }
    return crow::response(201); 
}
