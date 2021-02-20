#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include "pch.h"
#include "Helper.h"
#include "IdataBase.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "RoomMemberRequestHandler.h"


#include <thread>
#include <Windows.h>
#include <WinSock2.h>



using std::thread;

class Communicator
{


public:
	Communicator();
	Communicator(IDatabase* db);
	~Communicator();

	void bindAndListen();
	void handleRequests(SOCKET client_socket);

private:
	map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory* m_handlerFactory;
	SOCKET serverSocket;
	IDatabase* db;

	void startThreadForNewClient();

	IRequestHandler* sortRequest(Request r);

};

