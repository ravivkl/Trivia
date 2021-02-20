#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include "pch.h"
#include "json.hpp"
#include "ResponseStructures.h"
#include "RequestStructures.h"
#include <vector>
#include <string>
#include <WinSock2.h>


#define ID "ID"
#define IS_ACTIVE "isActive"
#define MAX_PLAYERS "maxPlayers"
#define NAME "name"
#define TIME_PER_QUESTION "timePerQuestion"
#define QUESTION_NUM "numOfQustion"

#define DATA "data"

class Helper
{
public:
	static void print(char msg[]);
	static int getMessageSize(char msg[]);
	static char getMessageTypeCode(char msg[]);
	static string getDictPartOfMessage(vector<Byte> & buf);
	static void sendData(SOCKET sc, char* msg);
	static void sendData(SOCKET sc, std::string message);
	static void sendData(SOCKET sc, vector<Byte> message);
	static vector<Byte> toBytes(string msg);
	static vector<Byte> toBytes(const char msg[], int size);

	static string toString(vector<Byte>);
	static char* serializeFirstResponse(unsigned int status, unsigned int length);
	static vector<Byte> msgToProtocol(vector<Byte> json, int code);


	static nlohmann::json vectorToJson(const vector<RoomData> vec);
	static nlohmann::json vectorToJson(const vector<string> vec);

};


#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

#else // we want nothing to be printed in release version
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define TRACE(msg, ...) // do nothing
#endif
