#pragma once
#include <string>
#include <vector>
#include "Client.h"
#include "Utility.h"

// ����� "�����"
// �������� �������� ��� �������������� � ������� �����
class Weapon;

class Player : public Client
{
private:
	int hitpoints; // ���� �������� 
	void kill();

public:
	static const int inventory_size;
	static const float pickup_reach_distance;

	utility::Vector2 pos;
	int weapon_count;
	std::vector<Weapon*> inventory;
	Weapon* weapon; // ������� (��������) ������ � �����

	Player(std::string, int, utility::Vector2);
	~Player();
	void attack(Player&);
	void pickup_weapon(Weapon&);
	void drop_weapon(const int);
	void select_weapon(const int);
	std::string ToString() const;
	Player& operator=(Connection&) override;
};

std::ostream& operator<<(std::ostream&, const Player&);