#include "Utility.h"
using std::string;

string utility::uint_to_str(unsigned int n)
{
	if (n == 0) return "0";
	string str;
	char* buff = (char*)malloc(12);
	int index = 0;
	while (n > 0)
	{
		buff[index] = (n % 10) + '0';
		n /= 10;
		++index;
	}

	while (index > 0)
	{
		--index;
		str += buff[index];
	}

	free(buff);
	return str;
}

bool utility::is_connected_to_internet()
{
	return true;
}

string utility::get_ip_address()
{
	if (!is_connected_to_internet()) throw connection_error("Cannot get IP address: no Internet connection");
	return "127.0.0.1";
}

int utility::get_free_port()
{
	return 8000;
}

string utility::time_to_datetime(time_t curr_t)
{
	std::tm t;
	_localtime64_s(&t, &curr_t);
	const string date = uint_to_str(t.tm_mday) + "/" + uint_to_str(t.tm_mon + 1) + "/" + uint_to_str(t.tm_year + 1900);
	const string time = uint_to_str(t.tm_hour) + ":" + uint_to_str(t.tm_min) + ":" + uint_to_str(t.tm_sec);
	return date + " " + time;
}

utility::Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

utility::Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float utility::Vector2::dist_squared(const Vector2 a, const Vector2 b)
{
	const float dx = b.x - a.x;
	const float dy = b.y - a.y;
	return dx * dx + dy * dy;
}

utility::Pair<double, double> utility::SinCos(double radians)
{
	return utility::Pair<double, double>(sin(radians), cos(radians));
}