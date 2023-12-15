#pragma once
#include "Weapon.h"
#include "Player.h"
#include "Utility.h"
#include <iostream>

class Pistol : public Weapon
{
private:
	static const int max_ammo;
	static const int default_dmg;

protected:
	int ammo;

public:
	Pistol(const utility::Vector2&);
	Pistol(Player&);

	void on_pickup(Player&);
	void on_attacking() const override;
	void on_attacking_not_virtual() const;
	std::string ToString() const;
};

std::ostream& operator<<(std::ostream&, const Pistol&);