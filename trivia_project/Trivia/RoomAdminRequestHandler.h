#pragma once


#include "pch.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : IRequestHandler
{
public:
	RoomAdminRequestHandler(Room&,RoomManager*);
	bool isRequestRelevant(Request r);
	RequestResult handleRequest(Request r, LoggedUser user);

	static bool isRoomAdminRequest(unsigned int id);

private:
	Room m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;

	RequestResult closeRoom(Request r);
	RequestResult startGame(Request r);
	RequestResult getRoomState(Request r);

};
