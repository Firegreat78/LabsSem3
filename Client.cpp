#include "Client.h"
#include "Host.h"
#include "Connection.h"
#include "Utility.h"
#include "connection_error.h"
#include <string>
#include <stdexcept>
#include <ctime>

using std::string;
using std::tm;

inline string int_to_str(int integer) // unsigned
{
	if (integer == 0) return "0";
	string str;
	char* buff = (char*)malloc(13);
	int index = 0;
	while (integer > 0)
	{
		buff[index] = (integer % 10) + '0';
		integer /= 10;
		--index;
	}

	while (index > 0)
	{
		--index;
		str += buff[index];
	}

	free(buff);
	return str;
}

// если нет интернета - экземпляр 
// класса connection не будет создан
Client::Client(string username) : Connection()
{
	this->username = username;
	this->login_time = time(0);
}

// 11/12/2023 18:32:31
string Client::login_time_as_datetime() const
{
	return utility::time_to_datetime(this->login_time);
}

string Client::GetNickname()
{
	return this->username;
}

Client& Client::operator=(Connection& conn)
{
	this->ip_address = conn.ip_address;
	this->port = conn.port;
	return *this;
}