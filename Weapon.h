#pragma once
#include "Player.h"
#include "Utility.h"

class Pistol;

class Weapon // abstract
{
	friend void Player::attack(Player&);
	friend void Player::pickup_weapon(Weapon&);
	
	int damage;

protected:
	Player* owner;
	utility::Vector2* pos;

public:
	Weapon(const utility::Vector2&, const int);
	Weapon(Player&, const int);
	virtual void on_attacking() const;
	void on_attacking_not_virtual() const;
	virtual ~Weapon() = 0;
	void on_pickup(Player&);
	void on_drop();
	void test_virtual() const; // для теста вызова on_attacking
	std::string ToString() const;
};