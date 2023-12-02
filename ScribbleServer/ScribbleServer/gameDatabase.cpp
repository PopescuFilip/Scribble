#include "gameDatabase.h"

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

void GameStorage::PopulateStorage()
{
    std::ifstream file{ kWordFile };
    std::string string;

    while (std::getline(file, string))
    {
        m_db.insert(Word{ string });
    }

    file.close();
}
