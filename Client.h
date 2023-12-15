#pragma once
#include <string>
#include <ctime>
#include "Connection.h"

// ������ (�������)
// �������������� ��� ������
class Client : public Connection
{
protected:
	std::string username; // ��� ������

public:
	Client(std::string);
	std::string login_time_as_datetime() const;
	std::string GetNickname();

	virtual Client& operator=(Connection&);
};
