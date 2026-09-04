#include "Player.h"
#include <Input/Input.h>
#include <Level/GameLevel.h>
#include <Game/Game.h>

using namespace Craft;
Player::Player(const Craft::Vector2& position)
	:Actor(L"P", position, Color::Green)
{
	sortingOrder = 10;
}

void Player::Tick(float deltaTime) {
	super::Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_ESCAPE)) {
		return;
	}

	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());

	if (Input::Get().GetKeyDown(VK_RIGHT)) {
		Vector2 newPosition = GetPosition();
		newPosition.x += 1;

		if (level && level->CanMove(GetPosition(), newPosition)) {
			SetPosition(newPosition);
		}
	}
	if (Input::Get().GetKeyDown(VK_LEFT)) {
		position.x;

		Vector2 newPosition = GetPosition();
		newPosition.x -= 1;

		if (level && level->CanMove(GetPosition(), newPosition)) {
			SetPosition(newPosition);
		}
	}
	if (Input::Get().GetKeyDown(VK_UP)) {
		Vector2 newPosition = GetPosition();
		newPosition.y -= 1;

		if (level && level->CanMove(GetPosition(), newPosition)) {
			SetPosition(newPosition);
		}
	}
	if (Input::Get().GetKeyDown(VK_DOWN)) {
		Vector2 newPosition = GetPosition();
		newPosition.y += 1;

		if (level && level->CanMove(GetPosition(), newPosition)) {
			SetPosition(newPosition);
		}
	}
}