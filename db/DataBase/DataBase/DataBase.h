#pragma once
#include "../../../sqlite-amalgamation-3310100/sqlite3.h"
#include <string>
#include <io.h>
#include "../../../trivia_project/trivia_project/IDataBase.h"
#include <fstream>



class DataBase : IDataBase
{
public:
	DataBase();
	bool createUserTable();
	bool createQuestionTable();
	bool createStatisticTable();


	bool doesUserExists(const std::string& username);
	bool doesPassMeet(const std::string& password, const std::string& username);

	void addUser(std::string username, std::string password, std::string email);

	float getPlayersAvaAnswerTime(std::string username);
	int getNumOfCorrectAnswers(std::string username);
	int getNumOfTotalAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);

	std::vector<std::string> getUsers();

	

	bool createDB();

private:
	sqlite3* db;

	unsigned int indexGrow;
	void addQuestions();
	void putResponseIntoTable(std::string ans);
	std::string getCurrentSentence(std::string ans, unsigned int index);
	void putQuestionInTable(std::string que, std::string corrAns, std::string Ans[]);
};


