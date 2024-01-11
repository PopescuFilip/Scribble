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

static const std::unordered_map<std::string, GameState> mappedGameState{
	{ "Not Started",GameState::NotStarted},
	{ "Between Rounds",GameState::BetweenRounds},
	{ "Running", GameState::Running},
	{ "Ended", GameState::Ended}
};

static const GameState GetGameStateFromString(const std::string& string);

static const GameState GetGameStateFromString(const std::string& string)
{
	return mappedGameState.at(string);
}