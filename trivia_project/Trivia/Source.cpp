#include "pch.h"
#include "Server.h"
#include "SqliteDatabase.h"
#include "WSAInitializer.h"

int main()
{
	//init sock
	WSAInitializer wsa;

	try
	{
		//start the server
		SqliteDatabase * db = new SqliteDatabase();
		Server server((IDatabase*)db);
		server.run();
	}
	catch (...)
	{
		exit(1);
	}

	return 0;
}


