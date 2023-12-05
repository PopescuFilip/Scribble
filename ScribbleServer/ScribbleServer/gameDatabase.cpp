#include "gameDatabase.h"
#include <fstream>
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

void GameStorage::PopulateStorage()
{
    std::ifstream file{ kWordFile };
    std::string wordFromFile;

    while (std::getline(file, wordFromFile))
    {
        m_db.insert(Word{ wordFromFile });
    }

    file.close();
}
