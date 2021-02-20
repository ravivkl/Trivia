#include "JsonRequestPacketDeserializer.h"

using std::cout;
using std::endl;
using std::string;

using namespace nlohmann;

#define PASS_KEY "password"
#define USER_KEY "username"
#define EMAIL_KEY "email"
#define ROOMID_KEY "roomId"
#define ANSWER_TIMEOUT_KEY "answerTimeout"
#define MAX_USERS_KEY "maxUsers"
#define QUESTION_COUNT_KEY "questionCount"
#define ROOM_NAME_KEY "roomName"
#define STATUS "status"
#define ANSWER "answer"

/*
the function deserialize from vector of bytes into signup request
input: vector of bytes
output: signup request
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<Byte> buffer)
{
	//define vars
	SignupRequest ret;


	//string of dict/json into json object
	auto j = json::parse(Helper::getDictPartOfMessage(buffer));
	
	//get request vals
	ret.email = j[EMAIL_KEY].get<string>();
	ret.username = j[USER_KEY].get<string>();
	ret.password = j[PASS_KEY].get<string>();

	return ret;
}


/*
the function deserialize from vector of bytes into login request
input: vector of bytes
output: login request
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<Byte> buffer)
{
	//define vars
	LoginRequest ret;
	json j;

	//string of dict/json into json object
	j = json::parse(Helper::getDictPartOfMessage(buffer));

	//get request vals
	ret.username = j[USER_KEY].get<string>();
	ret.password = j[PASS_KEY].get<string>();

	return ret;
}


/*
The function deserialize the vecotr of bytes into GetPlayersInRoom request, via json.
input: vector of bytes, who follow a json schem.
output: GetPlayersInRoomRequest
*/
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(vector<Byte> buffer)
{
	GetPlayersInRoomRequest ret = { 0 };
	json j;

	j = json::parse(Helper::getDictPartOfMessage(buffer));

	ret.roomId = j[ROOMID_KEY];

	return ret;
}

/*
The function deserialize the vecotr of bytes into JoinRoom request, via json.
input: vector of bytes, that follow a json schem.
output: JoinRoomRequest
*/
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(vector<Byte> buffer)
{
	JoinRoomRequest ret;
	json j;

	j = json::parse(Helper::getDictPartOfMessage(buffer));

	ret.roomId = j[ROOMID_KEY].get<int>();
	ret.name = j[NAME].get<string>();

	return ret;
}


CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(vector<Byte> buffer)
{
	CreateRoomRequest ret;
	

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));
	
	ret.answerTimeout = j[ANSWER_TIMEOUT_KEY].get<int>();
	ret.maxUsers = j[MAX_USERS_KEY].get<int>();
	ret.questionCount = j[QUESTION_COUNT_KEY].get<int>();
	ret.roomName = j[ROOM_NAME_KEY].get<string>();

	ret.username = j[USER_KEY].get<string>();
	return ret;
}

GetRoomsRequest JsonRequestPacketDeserializer::deserializeGetRoomsRequest(vector<Byte> buffer)
{
	GetRoomsRequest ret;

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));
	ret.status = j[STATUS].get<unsigned int>();

	return ret;
}

CloseRoomRequest JsonRequestPacketDeserializer::deserializeCloseRoomRequest(vector<Byte> buffer)
{
	CloseRoomRequest ret = { 0,0 };

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));
	try
	{
		ret.roomId = j[ROOMID_KEY].get<unsigned int>();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	
	return ret;
}

StartGameRequest JsonRequestPacketDeserializer::deserializeStartGameRequest(vector<Byte> buffer)
{
	StartGameRequest ret;

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));
	ret.roomId = j[ROOMID_KEY];
	//ret.status = j[STATUS];

	return ret;
}

GetRoomStateRequest JsonRequestPacketDeserializer::deserializeGetRoomStateRequest(vector<Byte> buffer)
{
	GetRoomStateRequest ret;

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));
	ret.status = j[STATUS];

	return ret;
}

LeaveRoomRequset JsonRequestPacketDeserializer::deserializeLeaveRoomRequset(vector<Byte> buffer)
{
	LeaveRoomRequset ret;

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));

	ret.status = j[STATUS].get<unsigned int>();
	ret.roomId = j[ROOMID_KEY].get<unsigned int>();

	return ret;
}

LogoutRequest JsonRequestPacketDeserializer::deserializeLogoutRequest(vector<Byte> buffer)
{
	LogoutRequest ret;

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));

	ret.username = j[USER_KEY].get<string>();
	
	return ret;
}

GetStatusRequest JsonRequestPacketDeserializer::deserializeStatusRequest(vector<Byte> buffer)
{
	GetStatusRequest ret;

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));

	ret.username = j[USER_KEY].get<string>();

	return ret;
}

SubmitAnswerRequet JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(vector<Byte> buffer)
{
	SubmitAnswerRequet ret;

	auto j = json::parse(Helper::getDictPartOfMessage(buffer));
	
	ret.answerId = j[ANSWER].get<unsigned int>();

	return ret;
}
