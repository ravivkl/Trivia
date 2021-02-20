#include "Question.h"



Question::Question() 
{
}

Question::Question(string question, vector<string> answers, unsigned int correctAnswer)
{
	this->m_question = question;
	this->m_possibleAnswers = answers;
	this->correctAnswer = correctAnswer;
}

Question::Question(Question& other)
{
	this->m_possibleAnswers = other.m_possibleAnswers;
	this->m_question = other.m_question;
	this->correctAnswer = other.correctAnswer;
}

string Question::getQuestion()
{
	return this->m_question;
}

vector<string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

string Question::getCorrentAnswer()
{
	return this->m_possibleAnswers.front();
}



