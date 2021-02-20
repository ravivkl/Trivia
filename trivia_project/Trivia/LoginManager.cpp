#include "LoginManager.h"

//Declare the static members. The declaretion in the header isnt sufficient enough
mutex LoginManager::signupLock;
mutex LoginManager::loggedUsersLock;

vector<LoggedUser> LoginManager::m_loggedUsers;

//setter
void LoginManager::setDatabase(IDatabase * db)
{
	this->m_database = db;
}

//C'tors
LoginManager::LoginManager()
{
	this->m_database = nullptr;
}
LoginManager::LoginManager(IDatabase & db)
{
	this->m_database = &db;
}

//D'tor
LoginManager::~LoginManager()
{
	this->m_loggedUsers.clear();
}

//signup
void LoginManager::signup(string name, string pass, string email)
{
	
	LoginManager::signupLock.lock(); //Prevent other threads from signing up.

	this->m_database->signup(name, pass, email);
	
	LoginManager::signupLock.unlock();



	//Since login doesnt change the database, just reading from it, no lock is needed.
	this->login(name, pass);
}

//login
void LoginManager::login(string name, string pass)
{
	LoggedUser* user = new LoggedUser(name);
	
	//Check if user is aleady logged in.

	auto index = std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), *user);

	delete user;
	if (index != this->m_loggedUsers.end())
	{
		throw exception("error! User is already is logged in");
	}

	user = this->m_database->login(name, pass);
	if (user == nullptr)
	{
		throw exception("error! username or password is incorrect");
	}
	this->m_loggedUsers.push_back(*user);
}

//The function LoginManager::logout gets a LoggedUser and deletes it from the vector of logged users.
//Input: A user to delete.
//Output: true if the user was deleted successfully, false if not.
bool LoginManager::logout(LoggedUser user)
{
	auto index = std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), user);

	//std::find return iterator to the end of the contanair given, if the given item to find was not found.
	if (index != this->m_loggedUsers.end())
	{
		//Prevent access for other threads using this vector.
		LoginManager::loggedUsersLock.lock(); 


		//Since index is not the end of the contanair, index can be erased safely.
		this->m_loggedUsers.erase(index);
		
		//Done messing with the vector.
		LoginManager::loggedUsersLock.unlock();
		
		return true; //The user was found and deleted successfully.
	}

	//the user doesnt exist.
	return false;
}

//check if user exist
bool LoginManager::doesUserExiste(string user)
{
	return this->m_database->doesUserExiste(user);
}
