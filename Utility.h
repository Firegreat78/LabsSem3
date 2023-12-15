#pragma once
#include <string>
#include <ctime>
#include "connection_error.h"

namespace utility
{
	struct Vector2
	{
		float x, y;

		Vector2();
		Vector2(float, float);

		static float dist_squared(const Vector2 a, const Vector2 b);
	};

	template<class T1, class T2>
	struct Pair
	{
		T1 first;
		T2 second;

		Pair(T1 a, T2 b)
		{
			first = a;
			second = b;
		}
	};

	bool is_connected_to_internet();
	std::string get_ip_address();
	int get_free_port();
	std::string time_to_datetime(time_t);
	std::string uint_to_str(unsigned int);
	Pair<double, double> SinCos(double);
}