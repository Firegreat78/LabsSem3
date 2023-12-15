#pragma once
#include <stdexcept>
#include <string>
class connection_error : public std::logic_error
{
public:
	explicit connection_error(const std::string& msg) : std::logic_error(msg.c_str()) {}

	explicit connection_error(const char* msg) : std::logic_error(msg) {}
};

