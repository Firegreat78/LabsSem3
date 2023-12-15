#include "Pistol.h"
#include "game_error.h"
#include <iostream>

using utility::Vector2;
using std::string;
using std::ostream;
using std::cout;

const int Pistol::max_ammo = 50;
const int Pistol::default_dmg = 17;

Pistol::Pistol(const Vector2& pos) : Weapon(pos, default_dmg)
{
	this->ammo = max_ammo;
}

Pistol::Pistol(Player& player) : Weapon(player, default_dmg)
{
	this->ammo = max_ammo;
}

ostream& operator<<(ostream& s, const Pistol& p)
{
	return s << p.ToString();
}

string Pistol::ToString() const // перегрузка метода баз. класса с вызовом
{
	string str = Weapon::ToString();
	auto it1 = str.begin();
	return str.replace(it1, it1 + 6, "Pistol");
}

void Pistol::on_pickup(Player& player) // перегрузка метода баз. класса без вызова
{
	if (player.weapon_count == player.inventory_size)
		throw game_error("Cannot pick up a weapon: inventory is full");
	this->owner = &player;
	free(this->pos);
	this->pos = nullptr;
	cout << player << " picked up a pistol " << *this << '\n';
}

void Pistol::on_attacking() const
{
	cout << "Pistol shooting!\n";
}

void Pistol::on_attacking_not_virtual() const
{
	cout << "Pistol shooting!\n";
}
