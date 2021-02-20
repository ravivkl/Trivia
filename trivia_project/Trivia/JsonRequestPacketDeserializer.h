#pragma once

#include "RequestStructures.h"
#include "pch.h"
#include "json.hpp"
#include "Helper.h"

static class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(vector<Byte> buffer);
	static SignupRequest deserializeSignupRequest(vector<Byte> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(vector<Byte> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(vector<Byte> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(vector<Byte> buffer);
	static GetRoomsRequest deserializeGetRoomsRequest(vector<Byte> buffer);
	static CloseRoomRequest deserializeCloseRoomRequest(vector<Byte> buffer);
	static StartGameRequest deserializeStartGameRequest(vector<Byte> buffer);
	static GetRoomStateRequest deserializeGetRoomStateRequest(vector<Byte> buffer);
	static LeaveRoomRequset deserializeLeaveRoomRequset(vector<Byte> buffer);
	static LogoutRequest deserializeLogoutRequest(vector<Byte> buffer);
	static GetStatusRequest deserializeStatusRequest(vector<Byte> buffer);
	static SubmitAnswerRequet deserializeSubmitAnswerRequest(vector<Byte> buffer);
};