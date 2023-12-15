#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include "LongNumber.h"
#include "MyString.h"
#include "Player.h"
#include "Host.h"
#include "Utility.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Sword.h"

using namespace std;
using namespace utility;


Host host;
int main()
{
	// Weapons - ToString, cout:
	Pistol pistol1(Vector2(1, 3));
	Sword sword1(Vector2(3, 1));
	cout << "Weapons - ToString, cout:\n";
	cout << pistol1 << '\n' << sword1 << '\n';

	// перегрузка оператора =
	Connection a;
	Connection b;
	Client client("Nick");
	client.connect(host);
	Player pl("Player1", 100, Vector2(5, 12));
	pl = b;

	// virtual
	Pistol pistol(pl);
	Sword sword(pl);
	Weapon& wpPistol = pistol;
	Weapon& wpSword = sword;

	cout << "test_virtual:\n";
	wpPistol.test_virtual();
	wpSword.test_virtual();
	cout << "on_attacking:\n";
	wpPistol.on_attacking();
	wpSword.on_attacking();

	cout << "on_attacking_not_virtual:\n";
	wpPistol.on_attacking_not_virtual();
	wpSword.on_attacking_not_virtual();


	// SinCos:
	for (double rad = 0; rad < 2*3.1415926; rad += (3.1415926/32))
	{
		const auto sc = SinCos(rad);
		cout << "Radians: " << rad << ", SinCos: (" << sc.first << "; " << sc.second << ")\n";
	}
}
