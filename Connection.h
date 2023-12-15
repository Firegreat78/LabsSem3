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
	std::string ip_address; // адрес компьютера, с которого подключаемся к хосту
	int port;
	
public:
	Connection();
	void connect(Host& host);
	void disconnect(Host& host);
};
