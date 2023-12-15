#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include "Connection.h"
class Host // Хост
{
	friend void Connection::connect(Host&);
	friend void Connection::disconnect(Host&);
	const static size_t max_connections;
	std::unordered_map<std::string, Connection*> connections; // ip:conn

public:
	size_t connection_count() const;
};

