#pragma once
#include <stdexcept>
#include <string>
class game_error : public std::logic_error
{
public:
	explicit game_error(const std::string& msg) : std::logic_error(msg.c_str()) {}

	explicit game_error(const char* msg) : std::logic_error(msg) {}
};

