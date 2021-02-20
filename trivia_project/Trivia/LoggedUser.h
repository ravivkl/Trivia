#pragma once
#include <iostream>
#include <string>

using std::string;

class LoggedUser
{

public:
	LoggedUser();
	LoggedUser(string name);
	LoggedUser(const LoggedUser& other);
	string getUsername() const;
	

	bool operator==(LoggedUser other);
	friend bool operator<(const LoggedUser& a, const LoggedUser& b);

	~LoggedUser();
private:
	string m_username;

};

