#include "Server.h"

/*
i dont think comments are necessary
*/

//C'tors
Server::Server(IDatabase * db)
{
	this->m_database = db;
	this->m_communicator = new Communicator(db);
}
Server::Server(IDatabase * db, RequestHandlerFactory reqHand, Communicator comunic)
{
	this->m_database = db;
	*this->m_handlerFactory = reqHand;
	*this->m_communicator = comunic;
}

//D'tor
Server::~Server()
{
	this->m_database->close();
	delete(this->m_database);
	delete(this->m_communicator);
}

//run the server
void Server::run()
{
	this->m_communicator->bindAndListen();
}
