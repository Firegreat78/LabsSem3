#pragma once
#include <string>
#include <ctime>
#include "Connection.h"

// клиент (аккаунт)
// конструируется при логине
class Client : public Connection
{
protected:
	std::string username; // ник игрока

public:
	Client(std::string);
	std::string login_time_as_datetime() const;
	std::string GetNickname();

	virtual Client& operator=(Connection&);
};
