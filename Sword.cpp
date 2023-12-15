#include "Sword.h"
#include "Player.h"
#include "game_error.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::ostream;
using utility::Vector2;

const int Sword::default_dmg = 34;

Sword::Sword(const Vector2& pos) : Weapon(pos, default_dmg) {}
Sword::Sword(Player& player) : Weapon(player, default_dmg) {}

string Sword::ToString() const // перегрузка метода баз. класса с вызовом
{
	string str = Weapon::ToString();
	auto it1 = str.begin();
	return str.replace(it1, it1 + 6, "Sword");
}

ostream& operator<<(ostream& s, const Sword& sw)
{
	s << sw.ToString();
	return s;
}

void Sword::on_pickup(Player& player) // перегрузка метода баз. класса без вызова
{
	if (player.weapon_count == player.inventory_size)
		throw game_error("Cannot pick up weapon: inventory is full");
	this->owner = &player;
	free(this->pos);
	this->pos = nullptr;
	cout << player << " picked up a sword" << *this << '\n';
}

void Sword::on_attacking() const
{
	cout << "Sword attacking!\n";
}

void Sword::on_attacking_not_virtual() const
{
	cout << "Sword attacking!\n";
}
