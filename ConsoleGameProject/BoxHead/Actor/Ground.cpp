#include "Ground.h"

using namespace Craft;
Ground::Ground(const Vector2& position) 
	:Actor(L" ", position)
{
	sortingOrder = 0;
}