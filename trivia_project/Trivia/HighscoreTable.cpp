#include "HighscoreTable.h"



HighscoreTable::HighscoreTable()
{
}

HighscoreTable::HighscoreTable(IDatabase* db)
{
	this->db = db;
}


HighscoreTable::~HighscoreTable()
{
}

bool HighscoreTable::isRequestRelevant(Request request)
{
	return GET_HISCORES_ID == request.id || GET_MY_DATA == request.id;
}

RequestResult HighscoreTable::handleRequest(Request request, LoggedUser user)
{
	RequestResult ret;
	if (GET_HISCORES_ID == request.id)
	{
		ret = this->getHighscores(request);
	}
	else if (GET_MY_DATA == request.id)
	{
		ret = this->getStatus(request);
	}
	return ret;
}

RequestResult HighscoreTable::getHighscores(Request)
{
	RequestResult ret;
	HighscoreResponse resp;

	auto top = this->db->getHighscores();
	for (auto i : top)
	{
		resp.highscores.push_back(i.first);
	}

	//create signup result
	resp.status = TRIVIA_OK;
	ret.response = JsonResponsePacketSerializer::serializerResponse(resp);
	ret.newHandler = this;
	return ret;
}

RequestResult HighscoreTable::getStatus(Request r)
{
	RequestResult ret;
	GetStatusRequest deserialized = JsonRequestPacketDeserializer::deserializeStatusRequest(r.buffer);
	GetStatusResponse resp;

	resp.data = this->db->getStatus(deserialized.username);

	if (resp.data.size() > 0)
	{
		resp.status = TRIVIA_OK;
		ret.response = JsonResponsePacketSerializer::serializerResponse(resp);
	}
	else
	{
		ErrorResponse err;
		err.message = "some error with db";
		ret.response = JsonResponsePacketSerializer::serializerResponse(err);
	}

	ret.newHandler = this;
	return ret;
}