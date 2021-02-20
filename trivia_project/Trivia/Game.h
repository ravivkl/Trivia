#pragma once
#include "Question.h"
#include "pch.h"
#include "LoggedUser.h"

//A struct that stores the data of a game.
typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
}GameData;


class Game
{
public:
	void removeUser(string username);
	void submitAnswer(LoggedUser,unsigned int);
private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;

};

