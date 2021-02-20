#include "Game.h"

void Game::removeUser(string username)
{
	LoggedUser toFind(username);

	auto it = this->m_players.find(toFind);

	if (it != this->m_players.end())
	{
		this->m_players.erase(it);
	}
}


//The function submitAnswer gets a LoggedUser and an answer id. If the answerId matchs the correct answer, His stats will be updated.
//Input: A loggedUser and an answer id.
//Output: None.
void Game::submitAnswer(LoggedUser user, unsigned int answerId)
{
	if (this->m_players[user].currentQuestion.getCorrectAnswer() == answerId)
	{
		this->m_players[user].correctAnswerCount++;
	}
	else
	{
		this->m_players[user].wrongAnswerCount++;
	}

}
