#pragma once


#include <string>

using std::string;

typedef struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;
	unsigned int numOfQuestion;
} RoomData;
