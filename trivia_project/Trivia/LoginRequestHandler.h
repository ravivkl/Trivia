#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "RequestStructures.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "SqliteDatabase.h"
#include "ResponseStructures.h"
#include "pch.h"


class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() {};
	~LoginRequestHandler() {};
	LoginRequestHandler(IDatabase& db);
	LoginRequestHandler(LoginManager* man);

	static bool isLoginRequest(unsigned int id) { return id == LOGIN_REQUEST_ID || id == (unsigned int)SIGNUP_ID; }
	bool isRequestRelevant(Request);
	RequestResult handleRequest(Request, LoggedUser user);
	void removeUser(LoggedUser);
private:
	LoginManager *m_loginManager;
	
	RequestResult logout(Request);
	RequestResult login(Request);
	RequestResult signup(Request);

};
