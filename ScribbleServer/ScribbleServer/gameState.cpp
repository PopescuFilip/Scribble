#include "gameState.h"

const std::string GetStringFromGameState(const GameState& gameState)
{
    return mappedGameState.at(gameState);
}
