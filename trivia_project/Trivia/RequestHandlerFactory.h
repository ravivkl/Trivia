#pragma once

#include "pch.h"
#include "Question.h"
#include "RoomManager.h"
#include "LoginManager.h"
#include "HighscoreTable.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"


class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Request r);
	RoomMemberRequestHandler* creaeteRoomMemberRequestHandler(Request r);
	HighscoreTable* createHighScoreHendler();

private:
	LoginManager* m_loginManager;
	RoomManager* m_roomManager;
	HighscoreTable m_highscoreTable;
};

