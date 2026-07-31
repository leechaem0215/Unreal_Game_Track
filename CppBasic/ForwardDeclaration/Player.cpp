#include "Player.h"
#include "Weapon.h"

Player::Player()
{
	weapon = new Weapon();
}

Player::~Player()
{
	if (weapon) {
		delete weapon;
	}
}
