#include "Zombie.h"

using namespace Craft;
Zombie::Zombie(const Vector2& position)
	:Actor(L"Z", position)
{
	sortingOrder = 5;
}
