#include "RoomAdminRequestHandler.h"

#define DELETE_ROOM_FALIED_ERROR_MESSAGE "Could not delete the room. The room id may be invalid."
#define UNKOWN_MESSAGE_ERROR_MESSAGE "Invalid request id"


RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room,RoomManager* rm)
{
	this->m_room = room;
	this->m_roomManager = rm;
}

bool RoomAdminRequestHandler::isRequestRelevant(Request req)
{
	return CLOSE_ROOM_REQUEST == req.id || START_GAME_REQUEST == req.id || GET_ROOM_STATE_REQUEST == req.id || LEAVE_ROOM_REQUEST == req.id;
}


//The function RoomAdminRequestHandler::handleRequest gets a general request, and handle it by its id.
//Input: A request.
//Output: A request result. If the request id is not known to the handler, an error respones will be sent.
RequestResult RoomAdminRequestHandler::handleRequest(Request req, LoggedUser user)
{
	RequestResult ret;
	ErrorResponse errResp;

	switch (req.id)
	{
	case START_GAME_REQUEST:
		ret = this->startGame(req);
		break;
	case CLOSE_ROOM_REQUEST:
		ret = this->closeRoom(req);
		break;
	case GET_ROOM_STATE_REQUEST:
		//TODO
		break;

	default:
		errResp.message = UNKOWN_MESSAGE_ERROR_MESSAGE;
		ret.response = JsonResponsePacketSerializer::serializerResponse(errResp);
		break;
	}

	return ret;
}

bool RoomAdminRequestHandler::isRoomAdminRequest(unsigned int id)
{
	return CLOSE_ROOM_REQUEST == id || START_GAME_REQUEST == id || GET_ROOM_STATE_REQUEST == id || LEAVE_ROOM_REQUEST == id;;
}

RequestResult RoomAdminRequestHandler::closeRoom(Request r)
{
	RequestResult result;
	CloseRoomResponse resp = { 0,0 };
	ErrorResponse errResp;
	resp.status = TRIVIA_OK;

	//Delete the room from the map of rooms.
	if (this->m_roomManager->deleteRoom(this->m_room.getRoomData().id))
	{
		//Serialize the respone to bytes.	
		result.response = JsonResponsePacketSerializer::serializerResponse(resp);
	}
	//The operation had failed - the room isnt close.
	else
	{
		errResp.message = DELETE_ROOM_FALIED_ERROR_MESSAGE;
		result.response = JsonResponsePacketSerializer::serializerResponse(errResp);
	}
	
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(Request r)
{
	RequestResult result;
	
	
	//TODO

	return result;
}
