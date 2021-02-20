#pragma once

#include "pch.h"

class Question
{

public:
	Question();
	Question(string question ,vector<string> answers,unsigned int correctAnswer);
	Question(Question&);
	
	string getQuestion();
	vector<string> getPossibleAnswers();
	string getCorrentAnswer();
	unsigned int getCorrectAnswer() const { return this->correctAnswer; };

private:
	string m_question;
	vector<string> m_possibleAnswers;
	unsigned int correctAnswer;

};

