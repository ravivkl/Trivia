#pragma once

#include <mutex>

#include "LoggedUser.h"
#include "IDatabase.h"
#include "pch.h"

using std::mutex;

class LoginManager
{

public:
	LoginManager();
	LoginManager(IDatabase& db);
	~LoginManager();

	void signup(string name, string pass, string email);
	void login(string username, string password);
	bool logout(LoggedUser);
	bool doesUserExiste(string user);
;

private:
	//The mutex signupLock locks every time signup is called, so 2 or more threads wont signup at the same time.
	static mutex signupLock;
	static mutex loggedUsersLock;

	IDatabase * m_database;
	static vector<LoggedUser> m_loggedUsers;

	void setDatabase(IDatabase* db);
};

