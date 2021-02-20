#pragma once

#include <iostream> 
#include <bitset>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <list>
#include <exception>

#define LOGIN_PASSWORD_OFFSET 2
#define LOGIN_PASSWORD_LEN_OFFSET 1
#define SIGNUP_PASSWORD_LEN_OFFSET 1
#define DICT_OFFSET 5
#define DEFAULT_SIZE 256
#define HEADER_OFFSET 4

#define GET_BYTE 0xFF
#define GET_BYTE_OFFSET 8

#define PORT 8826

#define LOGIN_REQUEST_ID 1
#define SIGNUP_REQUEST_ID 2

#define GET_PLAYERS_REQUEST 3
#define JOIN_ROOM_REQUEST 4
#define CREATE_ROOM_REQUEST 5
#define SIGNOUT_REQUEST 6
#define GET_ROOMS_REQUEST 7
#define GET_HISCORES_REQUEST 8
#define MENU_REQUEST_ID 9
#define LOGOUT_RESPONSE_ID 10
#define JOIN_ROOM_RESPONSE 11
#define CREATE_ROOM_RESPONSE 12

#define CLOSE_ROOM_REQUEST 13
#define START_GAME_REQUEST 14
#define GET_ROOM_STATE_REQUEST 15
#define LEAVE_ROOM_REQUEST 16
#define GET_MY_DATA 17
#define ERROR_RESPONSE_ID 100
#define TRIVIA_OK 0


using std::bitset;
using std::vector;
using std::string;
using std::to_string;
using std::ctime;
using std::tm;
using std::map;
using std::list;
using std::exception;
using std::cout;
using std::endl;

typedef std::bitset<8> Byte;

typedef enum RequestID
{
	LOGIN_ID = LOGIN_REQUEST_ID,
	SIGNUP_ID = SIGNUP_REQUEST_ID,
	GET_PLAYER_ID = GET_PLAYERS_REQUEST,
	JOIN_ROOM_ID = JOIN_ROOM_REQUEST,
	CREATE_ROOM_ID = CREATE_ROOM_REQUEST,
	SIGNOUT_ID = SIGNOUT_REQUEST,
	GET_ROOMS_ID = GET_ROOMS_REQUEST,
	GET_HISCORES_ID = GET_HISCORES_REQUEST,
	ERROR_ID = ERROR_RESPONSE_ID
}RequestID;
