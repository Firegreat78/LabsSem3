#pragma once
#include "Weapon.h"

class Player;

class Sword : public Weapon
{
	static const int default_dmg;
public:
	Sword(const utility::Vector2&);
	Sword(Player&);
	void on_pickup(Player&);
	void on_attacking() const override;
	void on_attacking_not_virtual() const;
	std::string ToString() const;
};

std::ostream& operator<<(std::ostream&, const Sword&);