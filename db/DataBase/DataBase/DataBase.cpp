#include "DataBase.h"

DataBase::DataBase()
{
	createDB();
}



bool DataBase::createUserTable()
{
	const char* sqlStatement = "CREATE TABLE User (\
USER_NAME TEXT PRIMARY KEY NOT NULL,\
PASSWORD TEXT NOT NULL,\
EMAIL TEXT NOT NULL); ";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << "\n";
		return false;
	}
	else
	{
		return true;
	}
}

bool DataBase::createQuestionTable()
{
	const char* sqlStatement = "CREATE TABLE Question (\
QUESTION TEXT PRIMARY KEY NOT NULL,\
RIGHT_ANS TEXT NOT NULL,\
ANS2 TEXT NOT NULL,\
ANS3 TEXT NOT NULL,\
ANS4 TEXT NOT NULL); ";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << "\n";
		return false;
	}
	else
	{
		return true;
	}

}

bool DataBase::createStatisticTable()
{
	const char* sqlStatement = "CREATE TABLE Statistic (\
AvrageTime INTEGER  NOT NULL,\
CorrectAnswers INTEGER NOT NULL,\
TotalAnswers INTEGER NOT NULL,\
TotalGames INTEGER NOT NULL,\
user_name TEXT NOT NULL,\
FOREIGN KEY(user_name) REFERENCES Users(USER_NAME)); ";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << "\n";
		return false;
	}
	else
	{
		return true;
	}
}


bool userExistence;
int doesUserExistsCallback(void* data, int argc, char** argv, char** azColName)
{

	if (argv[0] == "1")
	{
		userExistence = true;
	}
	userExistence = false;
	return 0;
}
bool DataBase::doesUserExists(const std::string& username)
{
	char* idChar;
	std::string sqlStatement = "select exists(select username from User where name = '" + username + "');";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), doesUserExistsCallback, NULL, &errMessage);
	return userExistence;
}

bool passMeet;
int doesPassMeetCallback(void* data, int argc, char** argv, char** azColName)
{
	if (argv[0] == "1")
	{
		passMeet = true;
	}
	passMeet = false;
	return 0;
}
bool DataBase::doesPassMeet(const std::string& password, const std::string& username)
{
	char* idChar;
	std::string sqlStatement = "select exists(select username from User where name = '" + username + "' and password = '" + password + "');";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), doesPassMeetCallback, NULL, &errMessage);
	return userExistence;
}

void DataBase::addUser(std::string username, std::string password, std::string email)
{
	std::string sqlStatement = "\
INSERT INTO Person(USERNAME, PASSWORD, EMAIL) values ('" + username + "','" + password + "', '" + email + "');";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
}

void DataBase::addQuestions()
{
	std::string line;
	std::string msg;
	std::ifstream myfile("../../../questions.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			msg += line;
		}
		myfile.close();

		putResponseIntoTable(msg);
	}

}


//put the questions from the file into the questions table
void DataBase::putResponseIntoTable(std::string ans)
{
	unsigned int index = 0;

	std::string question;
	std::string correctAns;
	std::string saver;
	std::string quesAns[3];

	while (ans[index] != '[') // jmg into the data part
	{
		(index)++;
	}
	(index)++; // to the first '{'

	
	for (int i = 0; i < 10; i++)
	{
		(index) += 82; //where the question start, first letter
		question = getCurrentSentence(ans, index);

		(index) += 20;
		index += indexGrow;
		correctAns = getCurrentSentence(ans, index);

		(index) += 24;
		index += indexGrow;
		for (int j = 0; j < 3; j++)
		{
			quesAns[j] = getCurrentSentence(ans, index);
			(index) += 3 ;
			index += indexGrow;
		}

		index++; // to the first '{'

		putQuestionInTable(question, correctAns, quesAns);

		
	}
}

std::string DataBase::getCurrentSentence(std::string ans, unsigned int index)
{
	unsigned int follow = index; //will follow the index and says where sentence is starting when index says the end
	while (ans[index] != '"')
	{
		index++;
	}
	std::string retAns;
	for (int i = follow; i < index; i++)
	{
		retAns += ans[i];
	}
	indexGrow = index - follow;
	return retAns;
}

void DataBase::putQuestionInTable(std::string que, std::string corrAns, std::string Ans[])
{
	std::string sqlStatement = "\
INSERT INTO Question(QUESTION, RIGHT_ANS, ANS2, ANS3, ANS4) values ('" + que + "','" + corrAns + "', '" + Ans[0] + "', '" + Ans[1] + "', '" + Ans[2] + "');";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << "\n";
	}
}



bool DataBase::createDB()
{

	std::string dbFileName = "MyDB.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);// 0 = exist, -1 doesnt

	int res = sqlite3_open(dbFileName.c_str(), &db);// open the sqlite file(if doesnt exit=st, create one)
	if (res != SQLITE_OK)//check if opened successfuly
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	if (doesFileExist == -1) // here we need to create the database
	{
		if (!createUserTable())
		{
			return false;
		}
		if (!createStatisticTable())
		{
			return false;
		}
		if (!createQuestionTable())
		{
			return false;
		}
		else // when created successfuly so i can add questions
		{
			addQuestions();
		}
	}
	return true;
}

float avgTime;
int getPlayersAvgAnswerTimeCallback(void* data, int argc, char** argv, char** azColName)
{
	avgTime = 0;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[0]) == "AvrageTime")
		{
			avgTime = atoi(argv[0]);
			break;

		}
	}
	return 0;

}


float DataBase::getPlayersAvaAnswerTime(std::string username)
{

	int (*func)(void*, int, char**, char**) = getPlayersAvgAnswerTimeCallback;
	std::string sqlStatement = "select AvrageTime from StatisticTable where user_name = '" + username + "';";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), func, NULL, &errMessage);
	return avgTime;
}




int CorrAns;
int getNumOfCorrectAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	avgTime = 0;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[0]) == "CorrectAnswers")
		{
			CorrAns = atoi(argv[0]);
			break;

		}
	}
	return 0;

}


int DataBase::getNumOfCorrectAnswers(std::string username)
{
	int (*func)(void*, int, char**, char**) = getNumOfCorrectAnswersCallback;
	std::string sqlStatement = "select CorrectAnswers from StatisticTable where user_name = '" + username + "';";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), func, NULL, &errMessage);
	return CorrAns;
}



int TotalAns;
int getNumOfTotalAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	avgTime = 0;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[0]) == "TotalAnswers")
		{
			TotalAns = atoi(argv[0]);
			break;

		}
	}
	return 0;

}


int DataBase::getNumOfTotalAnswers(std::string username)
{
	int (*func)(void*, int, char**, char**) = getNumOfTotalAnswersCallback;
	std::string sqlStatement = "select TotalAnswers from StatisticTable where user_name = '" + username + "';";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), func, NULL, &errMessage);
	return TotalAns;
}


int TotalGames;
int getNumOfPlayerGamesCallback(void* data, int argc, char** argv, char** azColName)
{
	avgTime = 0;
	for (int i = 0; i < argc; i++) {
		if (std::string(azColName[0]) == "TotalGames")
		{
			TotalGames = atoi(argv[0]);
			break;

		}
	}
	return 0;

}


int DataBase::getNumOfPlayerGames(std::string username)
{
	int (*func)(void*, int, char**, char**) = getNumOfPlayerGamesCallback;
	std::string sqlStatement = "select TotalGames from StatisticTable where user_name = '" + username + "';";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement.c_str(), func, NULL, &errMessage);
	return TotalGames;
}


std::vector<std::string> al;
int getUsersCallback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		al.push_back(argv[i]);
	}
	
	return 0;
}


std::vector<std::string> DataBase::getUsers()
{
	char* idChar;
	int (*func)(void*, int, char**, char**) = getUsersCallback;
	std::string sqlStatement = "select * from user;";
	char* errMessage = nullptr;
	return al;
}


