#include "LoggedUser.h"

/*
i dont think comments are necessary
*/

LoggedUser::LoggedUser()
{
	this->m_username = "unknown";
}

//C'tor
LoggedUser::LoggedUser(string name)
{
	this->m_username = name;
}

LoggedUser::LoggedUser(const LoggedUser& other)
{
	this->m_username = other.m_username;
}

bool LoggedUser::operator==(LoggedUser other)
{
	return this->m_username == other.m_username;
}

bool operator<(const LoggedUser& a, const LoggedUser& b)
{
	return a.m_username < b.m_username;
}

//D'tor
LoggedUser::~LoggedUser()
{
	this->m_username.clear();
}

//getter
string LoggedUser::getUsername() const 
{
	return this->m_username;
}
