#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "pch.h"
#include <io.h>

int loginCallback(void * data, int argc, char ** argv, char ** azColName);
int getQuestionsCallback(void * data, int argc, char ** argv, char ** azColName);

class SqliteDatabase : IDatabase
{

public:
	SqliteDatabase();
	~SqliteDatabase();

	virtual bool open();
	virtual void close();

	virtual map<string, int> getHighscores();
	virtual map<string, double> getStatus(string name);
	virtual bool doesUserExiste(const string);
	virtual list<Question> getQuestions(const int);

	// Inherited via IDatabase
	virtual void signup(string, string, string);
	virtual LoggedUser * login(string, string);
	virtual void logout(string, string);
	virtual void updateUserScore(string name, int correct, int worng, double avg) override;

private:
	sqlite3 * db;
};

