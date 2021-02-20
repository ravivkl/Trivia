#pragma once
#include "Game.h"
#include "Room.h"
#include "IDatabase.h"

class GameManager
{
public:
	GameManager();
	GameManager(IDatabase*);

	Game createGame(Room);

private:
	IDatabase* m_database;
	vector<Game> m_games;
};