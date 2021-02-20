#pragma once

#include "pch.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "LoginManager.h"
#include "HighscoreTable.h"
#include "IRequestHandler.h"



class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	MenuRequestHandler(RoomManager*);
	

	bool isRequestRelevant(Request  r);
	RequestResult handleRequest(Request r, LoggedUser user);

	static bool isMenuRequest(unsigned int id);


private:
	LoggedUser m_user;
	RoomManager* m_roomManager;
	HighscoreTable m_highscoreTable;
	RequestHandlerFactory* m_requestHandlerFactory;

	RequestResult createRoom(Request);
	RequestResult joinRoom(Request);
	RequestResult getPlayersInRoom(Request);
	RequestResult getRooms(Request);
};

