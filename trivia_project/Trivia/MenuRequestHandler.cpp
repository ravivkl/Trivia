#include "MenuRequestHandler.h"

void* watcher = nullptr;


MenuRequestHandler::MenuRequestHandler()
{
}

MenuRequestHandler::MenuRequestHandler(RoomManager* rm)
{
	this->m_roomManager = rm;
}

//return true if the request is relevant for this object, that is if the request id is MENU_REQUEST_ID
bool MenuRequestHandler::isRequestRelevant(Request r)
{
	//Check if any of the request is relevant for this class
	return JOIN_ROOM_RESPONSE == r.id || CREATE_ROOM_RESPONSE == r.id || GET_PLAYERS_REQUEST == r.id || JOIN_ROOM_REQUEST == r.id || CREATE_ROOM_REQUEST == r.id || GET_ROOMS_REQUEST == r.id || GET_HISCORES_REQUEST == r.id;
}



//Handle the request.
RequestResult MenuRequestHandler::handleRequest(Request r, LoggedUser user)
{
	RequestResult ret;
	ret.msg = "ERROR";


	if (this->isRequestRelevant(r))
	{
		switch (r.id)
		{
		case GET_PLAYERS_REQUEST:
			ret = this->getPlayersInRoom(r);
			break;
		case JOIN_ROOM_REQUEST:
			ret = this->joinRoom(r);
			break;
		case CREATE_ROOM_REQUEST:
			ret = this->createRoom(r);
			break;
		case GET_ROOMS_REQUEST:
			ret = this->getRooms(r);
			break;
		default:
			ErrorResponse er;
			er.message = "Request ID invalid";
			break;
		}
	}
	

	return ret;
}

bool MenuRequestHandler::isMenuRequest(unsigned int id)
{
	return JOIN_ROOM_REQUEST == id || CREATE_ROOM_REQUEST == id || GET_PLAYERS_REQUEST == id || JOIN_ROOM_REQUEST == id || CREATE_ROOM_REQUEST == id || SIGNOUT_REQUEST == id || GET_ROOMS_REQUEST == id;
}

//The function createRoom recive a request and create a room by the request configs.
//Input: A request.
//Output: A requestResult
RequestResult MenuRequestHandler::createRoom(Request r)
{
	RequestResult result;
	RoomData metadata;
	CreateRoomRequest req;
	CreateRoomResponse resp;
	bool exist = false;

	//Deserialize the request
	req = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(r.buffer);
	
	vector<RoomData> rooms = this->m_roomManager->getRoomsData();
	this->m_user = LoggedUser(req.username);


	for (auto curr : rooms)
	{
		if (curr.name == req.roomName)
		{
			exist = true;
			break;
		}
	}

	if (exist)
	{
		ErrorResponse err;
		err.message = "error! there is room with this name...";
		resp.status = ERROR_RESPONSE_ID;
		result.response = JsonResponsePacketSerializer::serializerResponse(err);
	}
	else
	{
		//config the room
		metadata.maxPlayers = req.maxUsers;
		metadata.name = req.roomName;
		metadata.timePerQuestion = req.answerTimeout;
		metadata.numOfQuestion = req.questionCount;
		metadata.isActive = false;

		//creates the room.
		resp.id = this->m_roomManager->createRoom(metadata, this->m_user);

		resp.status = TRIVIA_OK;
		result.response = JsonResponsePacketSerializer::serializerResponse(resp);
	}

	result.newHandler = this;


	return result;
}


//The function joinRoom adds the user this.m_user to a room with the given given in the request.
//Input:: vector of bytes.
//Output: The result of the operation (TRIVIA_OK or ERROR_RESPONSE_ID). 
RequestResult MenuRequestHandler::joinRoom(Request r)
{
	 RequestResult result;
	 JoinRoomResponse resp;
	 JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(r.buffer);

	 resp.status = TRIVIA_OK;
	 
	 watcher = (void*)&this->m_user;

	 //Try to add the user.
	 if (!this->m_roomManager->addUserToRoom(req.name, req.roomId))
	 {
		 //Failed to add the user. Change status accordingly.
		 resp.status = ERROR_RESPONSE_ID;
	 }
	 
	 //Serialize the response.
	 result.response = JsonResponsePacketSerializer::serializerResponse(resp);
	 result.newHandler = nullptr;


	 return result;
}

//The function getPlayersInRoom gets a vector of bytes, handle it and returns the result.
//Input: A vector of bytes.
//Output: A RequestResult
RequestResult MenuRequestHandler::getPlayersInRoom(Request r)
{
	RequestResult result;
	GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(r.buffer);
	GetPlayersInRoomResponse resp;



	//Get the vecotr of users
	vector<LoggedUser> users =  this->m_roomManager->getRoom(req.roomId)->getAllUsers();

	//get all the usernames from the vector of users.


	for (auto it = users.begin(); it != users.end(); it++)
	{
		resp.players.push_back((*it).getUsername());
	}

	result.response = JsonResponsePacketSerializer::serializerResponse(resp);
	result.newHandler = this;


	return result;
}

//The function getRoom gets a request and handle it.
//Input: A request 
//Output: A request result
RequestResult MenuRequestHandler::getRooms(Request r)
{
	RequestResult result;
	GetRoomsResponse resp;

	GetRoomsRequest req = JsonRequestPacketDeserializer::deserializeGetRoomsRequest(r.buffer);

	resp.rooms = this->m_roomManager->getRoomsData();
	 
	//Serializer the response to bytes
	result.response = JsonResponsePacketSerializer::serializerResponse(resp);
	result.newHandler = this;

	return result;
}
