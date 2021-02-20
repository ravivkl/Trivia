#include "Communicator.h"

/*
the function make a new thread to each client
Input: None
Output: None
*/
void Communicator::startThreadForNewClient()
{
	
	try
	{
		//the client socket
		SOCKET client_socket = ::accept(this->serverSocket, NULL, NULL);
		
		//invalid socket
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		
		cout << "Client accepted. Server and client can speak" << endl;

		//
		thread newThread(&Communicator::handleRequests, this, client_socket);
		newThread.detach();
	}
	catch (...)
	{
		//error!
		cout << "Can't connect to client..." << endl;
		exit(1);
	}
}

//C'tor
Communicator::Communicator()
{
	this->db = nullptr;
	this->m_handlerFactory = nullptr;
	//init server socket
	this->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//error!
	if (this->serverSocket == INVALID_SOCKET)
	{
		throw exception(__FUNCTION__ " - socket");
	}
}

/*
C'tor that get the data base
*/
Communicator::Communicator(IDatabase * db)
{
	//init all
	this->m_handlerFactory = new RequestHandlerFactory(db);
	this->db = db;
	this->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//error!
	if (this->serverSocket == INVALID_SOCKET)
	{
		throw exception(__FUNCTION__ " - socket");
	}
}

//D'tor
Communicator::~Communicator()
{
	try
	{
		//delete all
		delete this->m_handlerFactory;
		closesocket(this->serverSocket);
	}
	catch (...) {}
}

/*
the function bind the server socket and listen for clients
input: none
output: none
*/
void Communicator::bindAndListen()
{
	//define variable
	struct sockaddr_in sockAddr = { 0 };

	//Config the server socket
	sockAddr.sin_port = htons(PORT);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = 0000;

	//bind
	if (bind(this->serverSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	//listen to incoming messages.
	if (listen(this->serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
	std::cout << "Listening on port " << PORT << std::endl;

	//get new clients
	while (true)
	{
		cout << "Waiting for client connection request" << endl;
		startThreadForNewClient();
	}
}

/*
the function handle each client
input: client socket
output: none
*/
void Communicator::handleRequests(SOCKET client_socket)
{
	//define variables
	Request currentRequest;
	RequestResult res;
	IRequestHandler* currentHandler = (IRequestHandler*)-1;
	ErrorResponse err;
	currentRequest.id = (RequestID)0;
	LoggedUser thisUser;
	LoginRequestHandler crashLoginHandler;

	int ret = 0, size = 0;
	char msg[DEFAULT_SIZE] = { 0 };

	//while client not signout
	while (currentRequest.id != SIGNOUT_REQUEST)
	{
		//recv data
		ret = recv(client_socket, msg, DEFAULT_SIZE, 0);
		
		//connection has lost
		if (ret == INVALID_SOCKET || ret == SOCKET_ERROR)
		{
			cout << "Client " << client_socket << " closed the socket" << endl;
			
			break;
		}



		//get info of the msg
		size = Helper::getMessageSize(msg);
		currentRequest.buffer = Helper::toBytes(msg, size);
		currentRequest.id = (RequestID)Helper::getMessageTypeCode(msg);


		if (currentRequest.id == SIGNOUT_ID)
		{
			this->m_clients.erase(client_socket);

			//Logout.
			currentHandler = (IRequestHandler*)this->m_handlerFactory->createLoginRequestHandler();
			currentHandler->handleRequest(currentRequest,thisUser);
			closesocket(client_socket);
			break;
		} 

		//handle the message
		currentHandler = (IRequestHandler*)(this->sortRequest(currentRequest));


		if (currentHandler != nullptr)
		{
			this->m_clients[client_socket] = currentHandler;
			res = this->m_clients[client_socket]->handleRequest(currentRequest,thisUser);
		}

		//If sort request returned nullptr, no handler is matching the given request.
		else
		{
			res.response = JsonResponsePacketSerializer::serializerResponse(err);
			err.message = Helper::serializeFirstResponse(err.responseLength, ERROR_RESPONSE_ID);
			res.newHandler = currentHandler;
		}
		
		
		
		
		//send data to the client
		try
		{
			//sending data to client.
			Helper::sendData(client_socket, Helper::toString(res.response));
		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
		}
	}
}


//The function sortRequest gets a request, and returns a handler according to the request id.
//Input: A request.
//Output: An IRequestHandler, who point to a handler.
IRequestHandler* Communicator::sortRequest(Request req)
{
	IRequestHandler* handler = nullptr;	
	bool whatRequest = false;

	if (LoginRequestHandler::isLoginRequest(req.id))
	{
		handler = (IRequestHandler*)this->m_handlerFactory->createLoginRequestHandler();
	}

	else if (MenuRequestHandler::isMenuRequest((unsigned int)req.id))
	{
		handler = (IRequestHandler*)this->m_handlerFactory->createMenuRequestHandler();
	}

	else if (RoomAdminRequestHandler::isRoomAdminRequest(req.id))
	{
		handler = (IRequestHandler*)this->m_handlerFactory->createRoomAdminRequestHandler(req);
	}
	
	else if (HighscoreTable::isHighscoreRequest(req.id))
	{
		handler = (IRequestHandler*)this->m_handlerFactory->createHighScoreHendler();
	}
	
	else if (RoomMemberRequestHandler::isRoomMemeberRequest(req.id))
	{
		handler = (IRequestHandler*)this->m_handlerFactory->creaeteRoomMemberRequestHandler(req);
	}

	//if the id is not matching,return nullptr.
	return handler;
}

