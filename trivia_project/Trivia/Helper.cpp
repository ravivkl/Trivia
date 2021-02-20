#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

/*
the function print the data from client
input: msg
output: none
*/
void Helper::print(char msg[])
{
	//define var
	int i = 0;

	msg[0] += 30;

	if (strcmp(msg, "This is the SS"))
	{
		throw exception("Run! The nazi's are coming");
	}

	//print msg
	while (msg[i] != '}') //end of dict/json
	{
		cout << msg[i];
		i++;
	}
	cout << msg[i] << endl;
}

/*
the function get the size of the  data from client
input: msg
output: size
*/
int Helper::getMessageSize(char msg[])
{
	//get size
	for (int i = 0; i < DEFAULT_SIZE; i++)
	{
		//end of dict/json
		if (msg[i] == '}')
		{
			return(i + 1);
		}
	}
	//error!
	throw exception("the msg is to long! [Helper]");
}

/*
the function get the request code from client data
( it's only for the order, basically it's useless...)
input: msg
output: msg code
*/
char Helper::getMessageTypeCode(char msg[])
{
	return msg[0];
}

/*
the function get the dict/json part from msg
input: msg buf
output: string of the dict/json 
*/
string Helper::getDictPartOfMessage(vector<Byte> & buf)
{
	//define var
	string msgString = "";

	//get all the dict/json chars
	for (int i = DICT_OFFSET; i < buf.size(); i++)
	{
		msgString += (char)buf[i].to_ulong();
	}


	return msgString;
}

/*
the function send data
input: data string and socket
output: none
*/
void Helper::sendData(SOCKET sc, std::string message)
{
	//define var
	const char* data = message.c_str();
	int status = send(sc, data, (int)message.size(), 0);

	cout << "Message sent to client " << sc << "." << endl;

	//send the data
	if (status == INVALID_SOCKET)
	{
		//error!
		throw std::exception("Error while sending message to client " + status);
	}
}

/*
the function send data
input: data vector of bytes and socket
output: none
*/
void Helper::sendData(SOCKET sc, vector<Byte> message)
{
	//send 
	if (send(sc, (char*)(&message[0]), (int)message.size(), 0) == INVALID_SOCKET)
	{
		//error!
		throw std::exception("Error while sending message to client");
	}
}

vector<Byte> Helper::toBytes(string msg)
{
	return Helper::toBytes(msg.c_str(), (int)msg.size());
}

/*
the function encode string into vector of bytes
input: string to encode and her len
output: vector oc bytes
*/
vector<Byte> Helper::toBytes(const char msg[], int size)
{
	//define var
	vector<Byte> ret;

	//encode
	for (int i = 0; i < size; i++)
	{
		ret.push_back(Byte((unsigned long long)msg[i]));
	}

	return ret;
}

string Helper::toString(vector<Byte> vec)
{
	string str = "";
	int i = 0;

	for (i = 0; i < vec.size(); i++)
	{
		str += (char)vec[i].to_ulong();
	}


	return str;
}


char* Helper::serializeFirstResponse(unsigned int status, unsigned int length)
{
	string msg;

	msg += to_string(status);
	msg += to_string(length);
	
	return (char*)msg.c_str();
}

vector<Byte> Helper::msgToProtocol(vector<Byte> json, int code)
{
	vector<Byte> vec;
	int size = (int)json.size();
	
	Byte codeByte(code);
	int num = 0xff000000;

	vec.push_back(codeByte);

	for (int i = 0; i < 4; i++)
	{
		vec.push_back(num & size);
		num = num >> 8;
	}

	for (auto i : json)
	{
		vec.push_back(i);
	}

	return vec;
}

//The function vectorToJson gets a vector of type RoomData, and returns a json object.
//Input: Vector of RoomData. 
//Output: A json object. json[0] is vector[0], and json[1] is vector[1], and so on.
nlohmann::json Helper::vectorToJson(const vector<RoomData> vec)
{
	nlohmann::json j,currentRoom;

	for (int i = 0; i < vec.size(); i++)
	{
		//adds the data to the currentRoom
		currentRoom[ID] = to_string(vec[i].id);
		currentRoom[IS_ACTIVE] = to_string(vec[i].isActive);
		currentRoom[MAX_PLAYERS] = to_string(vec[i].maxPlayers);
		currentRoom[NAME] = vec[i].name;
		currentRoom[TIME_PER_QUESTION] = to_string(vec[i].timePerQuestion);
		currentRoom[QUESTION_NUM] = to_string(vec[i].numOfQuestion);

		//Adds the room to the json of rooms.
		j[to_string(i)] = currentRoom.dump();
		
		
	}

	cout << j.dump() << endl;

	return j;
}


//The function vectorToJson gets a vector of strings, and returns it as json format
nlohmann::json Helper::vectorToJson(const vector<string> vec)
{
	nlohmann::json j;

	for (int i = 0; i < vec.size(); i++)
	{
		j[to_string(i)] = vec[i];
	}

	return j;
}

void Helper::sendData(SOCKET sc, char* msg)
{
	string asString = msg;

	Helper::sendData(sc, asString);

}