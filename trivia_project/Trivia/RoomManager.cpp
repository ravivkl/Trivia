#include "RoomManager.h"

map<unsigned int, Room> RoomManager::m_rooms;
mutex RoomManager::roomsMutex;

RoomManager::RoomManager()
{
	this->nextID = 5;
}

//The functions createRoom adds a room to m_rooms.
//Input: LoggedUser to add to the room.
//Input: None.
unsigned int RoomManager::createRoom(RoomData metadata,LoggedUser user)
{
	metadata.id = this->nextID;

	//create a new room
	Room newRoom(metadata);
	newRoom.addUser(user);


	//Thread safety 
	roomsMutex.lock();
	
	//add the room to the room map
	this->m_rooms[this->nextID] = newRoom;

	roomsMutex.unlock();


	//return the room id, and after set the next id
	return this->nextID++;

}

//the function delete room remove a room from the room map.
//Input: id of the room to be deleted.
//Output: The operation status.
bool RoomManager::deleteRoom(unsigned int id)
{
	bool status = false;

	this->roomsMutex.lock();

	status = RoomManager::m_rooms.erase(id) == 1;
	
	this->roomsMutex.unlock();

	return status;
}

//The function addUser adds the user to a room with the given id.
//Input: A user to add, and an id of the room.
//Output: true if succeeded to add the user,false overwise.
bool RoomManager::addUserToRoom(LoggedUser user, unsigned int id)
{
	bool succeeded = false;

	this->roomsMutex.lock();

	//Try to add the user
	succeeded = this->m_rooms[id].addUser(user);
	
	this->roomsMutex.unlock();
	
	return succeeded;
}

//the function getRoomState return the state of the room with the given ID.
//Input: The ID of the room.
//Output: The room's state.
unsigned int RoomManager::getRoomState(unsigned int id)
{
	//No mutex is needed. m_rooms is not being change,only been read.
	return this->m_rooms[id].getRoomData().isActive;
}


//The function getRooms returns the metadata of all the rooms in m_rooms.
//Input: None.
//Output: vector of RoomData, which contains the metadata of all the rooms in m_rooms.  
vector<RoomData> RoomManager::getRoomsData()
{
	using namespace std;

	//the returned vector
	vector<RoomData> rooms;

	//go over the map with iterators.
	for each (auto currentRoom in RoomManager::m_rooms)
	{
		if(currentRoom.second.getRoomData().name != "")
			//No need for mutex. only reading from m_rooms, not writing.
			rooms.push_back(currentRoom.second.getRoomData());
	}

	return rooms;
}

//The function getRoom gets an id, and returns the room with that id.
//Input: And id (int)
//Output: A room with the id.
Room* RoomManager::getRoom(unsigned int id)
{
	//No need for mutex. only reading from m_rooms, not writing.
	return &this->m_rooms[id];
}
