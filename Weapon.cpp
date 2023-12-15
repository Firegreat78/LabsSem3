#include "Weapon.h"
#include "Utility.h"
#include "game_error.h"
#include <string>
#include <iostream>

using utility::Vector2;
using std::vector;
using std::string;
using std::cout;

Weapon::Weapon(const Vector2& pos, const int dmg)
{
	this->owner = nullptr;
	this->pos = new Vector2(pos);
	this->damage = dmg;
}

Weapon::Weapon(Player& player, const int dmg)
{
	if (player.weapon_count == player.inventory_size)
		throw game_error("Cannot add weapon to player: inventory is full");
	int freeslot = 0;
	while (player.inventory[freeslot] != nullptr) ++freeslot;
	++player.weapon_count;
	player.inventory[freeslot] = this;
	this->owner = &player;
	this->pos = nullptr;
	this->damage = dmg;
}

Weapon::~Weapon()
{
	if (this->pos != nullptr) free(this->pos);
}

void Weapon::on_pickup(Player& player)
{
	this->owner = &player;
	free(this->pos);
	this->pos = nullptr;
}

void Weapon::on_drop()
{
	this->pos = new Vector2(this->owner->pos);
	this->owner = nullptr;
}

string Weapon::ToString() const
{
	return "Weapon: {damage: " + utility::uint_to_str(this->damage) + "}"; // ...
}

void Weapon::on_attacking() const
{
	cout << "Weapon attack!\n";
}

void Weapon::on_attacking_not_virtual() const
{
	cout << "Weapon attack!\n";
}

void Weapon::test_virtual() const
{
	this->on_attacking();
}