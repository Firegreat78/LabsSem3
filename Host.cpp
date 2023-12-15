#include "Host.h"

const size_t Host::max_connections = 200;

size_t Host::connection_count() const
{
	return this->connections.size();
}