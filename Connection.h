#pragma once
#include <string>
#include <map>

class Host;

class Connection
{
	friend class Client;
	friend class Player;

protected:	
	size_t login_time;
	std::string ip_address; // ����� ����������, � �������� ������������ � �����
	int port;
	
public:
	Connection();
	void connect(Host& host);
	const int get_port() const;
	void disconnect(Host& host);
};
