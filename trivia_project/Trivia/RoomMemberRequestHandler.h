#pragma once

#include "Room.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"


class RoomMemberRequestHandler : IRequestHandler
{
public:
	RoomMemberRequestHandler(RoomManager* rm,Room* room);

	bool isRequestRelevant(Request);
	RequestResult handleRequest(Request, LoggedUser user);
	
	static bool isRoomMemeberRequest(unsigned int);

private:
	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;


	RequestResult leaveRoom(Request);
	RequestResult getRoomState(Request);

};
