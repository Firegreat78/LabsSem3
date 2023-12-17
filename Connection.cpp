#include "Connection.h"
#include "Utility.h"
#include "Host.h"
#include <string>
using std::string;

Connection::Connection()
{
	this->ip_address = utility::get_ip_address();
	this->port = utility::get_free_port(); // default
}

void Connection::connect(Host& host)
{
	this->login_time = time(0);
	if (host.connections.count(this->ip_address)) throw connection_error("Cannot connect to the host: this address is already connected to the host");
	else if (host.connection_count() == host.max_connections) throw connection_error("Cannot conect to the host: server is full");
	else host.connections[this->ip_address] = this;
}

void Connection::disconnect(Host& host)
{
	if (host.connections.count(this->ip_address)) host.connections.erase(this->ip_address);
	else throw connection_error("Cannot disconect from the host: this address is not connected to the host");
}

const int Connection::get_port() const
{
	return this->port;
}