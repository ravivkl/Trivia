#include "SqliteDatabase.h"

// ==============================================================================================================
// ----------------------------------------------------- CALLBACKS ----------------------------------------------
// ==============================================================================================================

/*
the func check if user is exist in db
input: all stuff of sqlite3
output: all stuff of sqlite3
*/
int existsCallback(void* data, int argc, char** argv, char** azColName)
{
	//is user exist?
	bool* exist = (bool*)data;
	atoi(argv[0]) ? *exist = true : *exist = false;
	return 0;
}

/*
the func get a user data from db
input: all stuff of sqlite3
output: all stuff of sqlite3
*/
int loginCallback(void* data, int argc, char** argv, char** azColName)
{
	//define var
	LoggedUser* user = (LoggedUser*)data;

	//get user
	if (argc == 1)
	{
		user = nullptr;
	}
	else
	{
		*user = LoggedUser(string(argv[0]));
	}

	return 0;
}

/*
the function get questions from db
input: all stuff of sqlite3
output: all stuff of sqlite3
*/
int getQuestionsCallback(void* data, int argc, char** argv, char** azColName)
{
	// :: NOTE ::
	//idk if it work...

	//define var
	list<Question>* questions = (list<Question>*)data;
	Question question;
	int i = 0;

	//error
	if (argc == 0)
	{
		throw exception("error! there are no questions");
	}

	//get question
	for (i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "correct_ans")
		{
			// DO STUFF
		}
		else if (string(azColName[i]) == "ans2")
		{
			// DO STUFF
		}
		else if (string(azColName[i]) == "ans3")
		{
			// DO STUFF
		}
		else if (string(azColName[i]) == "ans4")
		{
			// DO STUFF
		}
	}

	return 0;
}

int getHighCallback(void* data, int argc, char** argv, char** azColName)
{
	//define var
	map<string, int>* top = (map<string, int>*)data;
	int i = 0;

	//error
	if (argc == 0)
	{
		throw exception("error! there are no highscores");
	}

	for (i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == "name")
		{
			top->insert(std::pair<string, int>(string(argv[i]), atoi(argv[i - 1])));
		}
	}
	return 0;
}


int getStatusCallback(void* data, int argc, char** argv, char** azColName)
{
	//define var
	map<string, double>* top = (map<string, double>*)data;
	int i = 0;

	for (i = 0; i < argc; i++)
	{
		top->insert(std::pair<string, double>(string(azColName[i]), (double)atof(argv[i])));
	}
	return 0;
}

// ==============================================================================================================
// ------------------------------------------------------ METHODS -----------------------------------------------
// ==============================================================================================================

//C'tor
SqliteDatabase::SqliteDatabase()
{
	//setup the sqlite db 
	string dbFileName = "TriviaDatabase.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	char* errorMsg = nullptr;

	//if it not exist - create a new one
	if (EOF == doesFileExist)
	{
		//create all tables
		std::string sql("CREATE TABLE Question (question TEXT, question_id INTEGER, correct_ans TEXT, \
						ans2 TEXT, ans3 TEXT, ans4 TEXT, PRIMARY KEY(question_id));");
		sqlite3_exec(this->db, sql.c_str(), NULL, NULL, &errorMsg);

		sql = "CREATE TABLE User ( username TEXT, pass TEXT, email TEXT, PRIMARY KEY(username));";
		sqlite3_exec(this->db, sql.c_str(), NULL, NULL, &errorMsg);

		sql = "CREATE TABLE Game ( game_id INTEGER, status INTEGER, start_time TEXT, end_time TEXT, PRIMARY KEY(game_id)); ";
		sqlite3_exec(this->db, sql.c_str(), NULL, NULL, &errorMsg);

		sql = "CREATE TABLE UserScores ( name TEXT, avgTime FLOAT, correct INT, worng INT, games INT, PRIMARY KEY(name)); ";
		sqlite3_exec(this->db, sql.c_str(), NULL, NULL, &errorMsg);
	}
}

//D'tor
SqliteDatabase::~SqliteDatabase()
{
	//close db
	sqlite3_close(this->db);
	this->db = nullptr;
}

/*
the func open db
input: none
ouput: if open succeed
*/
bool SqliteDatabase::open()
{
	// :: NOTE :: 
	// the func is useless... it's same like in the c'tor

	//setup the db
	std::string dbFileName = "TriviaDatabase.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &this->db);

	//succeed?
	if (res != SQLITE_OK) {
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	return true;
}

/*
the func close db
input: none
ouput: none
*/
void SqliteDatabase::close()
{
	// :: NOTE :: 
	// the func is useless... it's same like in the d'tor

	//close db
	sqlite3_close(this->db);
	this->db = nullptr;
}

/*
the func get highscores
input: none
output: users with the score
*/
map<string, int> SqliteDatabase::getHighscores()
{
	// select * from Highscores order by score desc;	

	char* errorMsg = nullptr;
	map<string, int> topThree;
	//map<string, int>()
	std::string sql("select name, correct from UserScores order by correct desc limit 3;");
	//do sql
	sqlite3_exec(this->db, sql.c_str(), getHighCallback, &topThree, &errorMsg);

	return topThree;
}

map<string, double> SqliteDatabase::getStatus(string name)
{
	char* errorMsg = nullptr;
	map<string, double> data;
	std::string sql("select * from UserScores where name = '" + name + "';");
	sqlite3_exec(this->db, sql.c_str(), getStatusCallback, &data, &errorMsg);
	return data;
}

/*
the func check if a user exist in db
input: username
output: exist
*/
bool SqliteDatabase::doesUserExiste(const string name)
{
	//define vars
	char* errorMsg = nullptr;
	bool exist = false;
	std::string sql("select count(username) from USER where username = '" + name + "';");
	//do sql
	sqlite3_exec(this->db, sql.c_str(), existsCallback, &exist, &errorMsg);
	return exist;
}

/*
the func get questions
input: num of questions
output: list of questions
*/
list<Question> SqliteDatabase::getQuestions(const int num)
{
	// :: NOTE ::
	//idk if it work...

	//define vars
	list<Question> questions;
	char* errorMsg = nullptr;
	//do sql
	std::string sql("select * from Question where ROWNUM <= " + to_string(num) + ";");
	sqlite3_exec(this->db, sql.c_str(), NULL, &questions, &errorMsg);

	return questions;
}

/*
the function signup user in db
input: username password and email
output: none
*/
void SqliteDatabase::signup(string name, string pass, string email)
{
	//define vars and do sql
	char* errorMsg = nullptr;
	std::string sql("insert into User (username, pass, email) values ('" + name + "', '" + pass + "', '" + email + "');");
	sqlite3_exec(this->db, sql.c_str(), NULL, NULL, &errorMsg);
	sql = ("insert into UserScores (name, avgTime, correct, worng, games) values ('" + name + "', 0, 0, 0, 0);");
	sqlite3_exec(this->db, sql.c_str(), NULL, NULL, &errorMsg);
}

/*
the func login user
input: username and pass
output: user
*/
LoggedUser* SqliteDatabase::login(string name, string pass)
{
	//define vars
	LoggedUser* user = new LoggedUser();
	char* errorMsg = nullptr;
	std::string sql("select * from user where username = '" + name + "' and pass = '" + pass + "';");
	//do sql
	sqlite3_exec(this->db, sql.c_str(), &loginCallback, user, &errorMsg);

	//check if there is user
	if (&user == nullptr || user->getUsername() == "unknown")
	{
		return nullptr;
		//throw exception("error! username or password is incorrect");
	}

	return user;
}

void SqliteDatabase::logout(string name, string pass)
{
	// TODO
	// TODO
	// TODO TODO TODO TODO TODOOOOOOOOOOOO
	// DO DO DO DO
}

void SqliteDatabase::updateUserScore(string name, int correct, int worng, double avg)
{
	char* errorMsg = nullptr;
	std::string sql("update UserScores set games = games + 1, correct = correct + " +
		to_string(correct) + ", worng = worng + " + to_string(worng) +
		"avgTime = (case avgTime when 0 then " + to_string(avg) +
		"else (avgTime + " + to_string(avg) + ")/2 end)" + " where name = '" + name + "';");
	sqlite3_exec(this->db, sql.c_str(), NULL, NULL, &errorMsg);
}
