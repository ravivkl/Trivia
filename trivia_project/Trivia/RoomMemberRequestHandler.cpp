#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RoomManager* rm, Room* room)
{
	this->m_roomManager = rm;
	this->m_room = room;
}

bool RoomMemberRequestHandler::isRequestRelevant(Request r)
{
	return RoomMemberRequestHandler::isRoomMemeberRequest(r.id);
}

bool RoomMemberRequestHandler::isRoomMemeberRequest(unsigned int id)
{
	return id == LEAVE_ROOM_REQUEST || id == GET_ROOM_STATE_REQUEST;
}


RequestResult RoomMemberRequestHandler::handleRequest(Request req, LoggedUser user)
{
	RequestResult ret;
	ErrorResponse errResp;
	switch (req.id)
	{
	case LEAVE_ROOM_REQUEST:
		ret = this->leaveRoom(req);
		break;
	default:
		errResp.message = "Invalid request id";
		ret.response = JsonResponsePacketSerializer::serializerResponse(errResp);
		break;
	}

	ret.newHandler = this;

	return ret;
}

RequestResult RoomMemberRequestHandler::getRoomState(Request req)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveRoom(Request req)
{
	RequestResult ret;
	LeaveRoomRequset dereq = JsonRequestPacketDeserializer::deserializeLeaveRoomRequset(req.buffer);
	LeaveRoomResponse resp = { 0,0 };
	ErrorResponse errResp;

	//Get a pointer to the room, and remove this user from it.
	if (this->m_roomManager->getRoom(dereq.roomId)->removeUser(this->m_user.getUsername()))
	{
		//If the operation succeeded, deserialize a normal message.
		resp.status = TRIVIA_OK;
		ret.response = JsonResponsePacketSerializer::serializerResponse(resp);
	}
	//Could not deleted the user.
	else
	{
		//Serialize an error message.
		errResp.message = string("could not delete the user ") + this->m_user.getUsername() + string(" from the room");
		ret.response = JsonResponsePacketSerializer::serializerResponse(errResp);
	}
	

	ret.newHandler = this;

	return ret;
}
