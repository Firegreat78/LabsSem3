#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <algorithm>
#include <ranges>
#include "LongNumber.h"
#include "MyString.h"
#include "Player.h"
#include "Host.h"
#include "Utility.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Sword.h"

using std::vector;
using utility::Vector2;
using std::sort;
using std::copy_if;
using std::back_inserter;

Host host;

struct smaller
{
	template<class T>
	bool operator()(T const& a, T const& b) const { return a < b; }
};

int main()
{
	// поиск (фильтр)
	vector<Connection*> connections;
	vector<Connection*> filtered;
	Connection connection;
	Client client("Bob");
	Player player("Alex", 100, Vector2(0, 1));
	connections.push_back(&connection);
	connections.push_back(&client);
	connections.push_back(&player);

	copy_if(connections.begin(), connections.end(), back_inserter(filtered), 
		[](Connection* c) {return c->get_port() == 8001; });

	// сортировка по неубыванию
	vector<LongNumber> long_numbers;
	long_numbers.push_back(3);
	long_numbers.push_back(3345452020);
	long_numbers.push_back(-35342);
	long_numbers.push_back(-35344342);
	long_numbers.push_back(INT64_MAX);
	long_numbers.push_back(INT64_MIN);
	sort(long_numbers.begin(), long_numbers.end(), smaller());
}
