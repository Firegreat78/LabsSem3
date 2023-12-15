#include "Player.h"
#include "Weapon.h"
#include "game_error.h"
#include "Utility.h"
#include <iostream>

using std::string;
using utility::Vector2;
using std::ostream;

const float Player::pickup_reach_distance = 5;
const int Player::inventory_size = 4;

Player::Player(string username, int hp, Vector2 pos) : Client(username)
{
	this->hitpoints = hp;
	this->weapon = nullptr;
	this->inventory.resize(inventory_size, nullptr);
	this->weapon_count = 0;
	this->pos = pos;
}

void Player::attack(Player& target)
{
	if (this->weapon == nullptr) throw game_error("Error: cannot use weapon if none is in your hands");
	this->weapon->on_attacking();
	target.hitpoints -= this->weapon->damage;
	if (target.hitpoints <= 0) target.kill();
}

void Player::pickup_weapon(Weapon& weapon)
{
	if (weapon.owner != nullptr)
		throw game_error("Cannot pick up weapon that is in inventory");
	if (Vector2::dist_squared(this->pos, *weapon.pos) > (pickup_reach_distance * pickup_reach_distance))
		throw game_error("Weapon too far away!");
	if (this->weapon_count == inventory_size) throw game_error("Inventory is full!");
	this->inventory[this->weapon_count] = &weapon;
	weapon.on_pickup(*this);
}

void Player::drop_weapon(const int slot)
{
	if (slot < 0 || slot >= inventory_size)
		throw game_error("Invalid slot index");
	if (this->inventory[slot] == nullptr)
		throw game_error("Cannot drop weapon from an empty slot!");
	this->inventory[slot]->on_drop();
	this->inventory[slot] = nullptr;
}

void Player::select_weapon(const int slot)
{
	if (this->inventory[slot] == nullptr)
		throw game_error(string("Cannot select weapon on slot ") + string(1, '0' + slot) + string(": slot is empty"));
	this->weapon = this->inventory[slot];
}

void Player::kill()
{
	for (auto wp : this->inventory) { if (wp != nullptr) wp->on_drop(); }
	this->~Player();
}

Player::~Player() {}

string Player::ToString() const
{
	return this->username + " (" + this->ip_address + ")";
}

ostream& operator<<(ostream& s, const Player& p)
{
	return s << p.ToString();
}

Player& Player::operator=(Connection& conn)
{
	Client::operator=(conn);
	return *this;
}
