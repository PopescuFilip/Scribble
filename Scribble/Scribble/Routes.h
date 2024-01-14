#pragma once
#include <cpr/cpr.h>
#include <crow.h>
#include "GameState.h"

cpr::Response GetPlayers(const std::string& roomCode);
cpr::Response GetGameState(const std::string& roomCode);
cpr::Response GetWord(const int id, const std::string& roomCode);
cpr::Response GuessWord(const int id, const std::string& roomCode, const std::string& word);
cpr::Response GetProfile(const int id);
cpr::Response CreateRoom(const int id);
cpr::Response JoinRoomRoute(const int id,const std::string& roomCode);
cpr::Response CheckState(const int id,const std::string& roomCode);
cpr::Response CheckUser(const std::string& user,const std::string& password);
cpr::Response AddUser(const std::string& user,const std::string& password);
cpr::Response PutDrawing(const int id,const std::string& roomCode,const std::string& drawing);
cpr::Response Start(const int id,const std::string& roomCode);
