#pragma once

#include "pch.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
#include "Communicator.h"

class Server
{
	IDatabase * m_database;
	RequestHandlerFactory* m_handlerFactory;
	Communicator* m_communicator;

public:
	Server() {};
	Server(IDatabase * db);
	Server(IDatabase * db, RequestHandlerFactory reqHand, Communicator comunic);
	~Server();

	void run();
};

