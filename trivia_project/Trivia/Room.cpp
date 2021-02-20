#include "Room.h"


//Constructor
Room::Room(RoomData metadata)
{
	this->m_metadata = metadata;
}


/*
	add a user the the users list
*/
bool Room::addUser(const LoggedUser user)
{
	

	//Adds the user, only if there is place left.
	if (this->m_metadata.maxPlayers > (unsigned int)this->m_users.size())
	{
		this->m_users.push_back(user);
		return true; //Succeeded to add the user.
	}
	
	//Failed to add the  user.
	return false;
}

bool Room::removeUser(const string username)
{
	vector<LoggedUser>::iterator it;

	//go over the vector with iterator.
	for (it = this->m_users.begin(); it != this->m_users.end();)
	{
		
		if (it->getUsername() == username)
		{
			it = this->m_users.erase(it);
		}
		else
		{
			it++;
		}
	}

	return it == this->m_users.end();
}

const RoomData Room::getRoomData() const
{
	return this->m_metadata;
}

void Room::removeAllUsers()
{
	//Remove all the users from the room
	while (this->m_users.size() > 0)
	{
		this->m_users.pop_back();
	}
}

vector<LoggedUser> Room::getAllUsers() const 
{
	return this->m_users;
}
