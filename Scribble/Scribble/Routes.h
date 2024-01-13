#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include "GameState.h"

cpr::Response GetPlayers(const std::string& roomCode);
cpr::Response GetGameState(const std::string& roomCode);
cpr::Response GetWord(const int id, const std::string& roomCode);
cpr::Response GuessWord(const int id, const std::string& roomCode, const std::string& word);
