#pragma once

#include "pch.h"
#include "IRequestHandler.h"

// to avoid circular definition
class IRequestHandler;

typedef struct Request
{
	RequestID id;
	tm recivalTime;
	vector<Byte> buffer;

}Request;

typedef struct LoginRequest
{
	string password;
	string username;
}LoginRequest;

typedef struct SignupRequest
{
	string username;
	string password;
	string email;
}SignupRequest;

typedef struct LogoutRequest
{
	string username;
}LogoutRequest;

typedef struct RequestResult
{
	vector<Byte> response;
	string msg;
	IRequestHandler* newHandler;
}RequestResult;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
	string name;
}JoinRoomRequest;

typedef struct CreateRoomRequest
{
	string roomName;
	string username;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
}CreateRoomRequest;

typedef struct GetRoomsRequest
{
	unsigned int status;
}GetRoomsRequest;

typedef struct CloseRoomRequest
{
	unsigned int roomId;
	unsigned int status;
}CloseRoomRequest;

typedef struct StartGameRequest
{
	unsigned int roomId;
	unsigned int status;
}StartGameRequest;

typedef struct GetRoomStateRequest
{
	unsigned int status;
}GetRoomStateRequest;

typedef struct LeaveRoomRequset
{
	unsigned int roomId;
	unsigned int status;
}LeaveRoomRequset;

typedef struct GetStatusRequest
{
	string username;
}GetStatusRequest;

typedef struct SubmitAnswerRequet
{
	unsigned int answerId;
}SubmitAnswerRequet;