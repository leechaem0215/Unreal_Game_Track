#include "Wall.h"

using namespace Craft;
Wall::Wall(const Vector2& position)
	: Actor(L"#", position)
{
	sortingOrder = 2;
}