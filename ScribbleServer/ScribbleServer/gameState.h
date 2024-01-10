#pragma once
#include <unordered_map>
#include <string>

enum class GameState : uint8_t
{
	NotStarted,
	BetweenRounds,
	Running,
	Ended
};

static const std::unordered_map<GameState, std::string> mappedGameState{
	{GameState::NotStarted, "Not Started"},
	{GameState::BetweenRounds, "Between Rounds"},
	{GameState::Running, "Running"},
	{GameState::Ended, "Ended"}
};

static const std::string GetStringFromGameState(const GameState& gameState);

static const std::string GetStringFromGameState(const GameState& gameState)
{
	return mappedGameState.at(gameState);
}