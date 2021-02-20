#pragma once

#include "IDatabase.h"
#include "RequestStructures.h"
#include "ResponseStructures.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include <string>
#include <vector>

using std::string;
using std::vector;


class HighscoreTable : IRequestHandler
{
public:
	HighscoreTable();
	HighscoreTable(IDatabase* db);
	
	RequestResult getHighscores(Request);
	RequestResult getStatus(Request);

	~HighscoreTable();
	
	static bool isHighscoreRequest(unsigned int id) { return id == GET_HISCORES_ID || id == GET_MY_DATA;  };

	// Inherited via IRequestHandler
	virtual bool isRequestRelevant(Request) override;
	virtual RequestResult handleRequest(Request, LoggedUser user) override;

private:
	IDatabase *db;


};

