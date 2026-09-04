#include "Game.h"
#include <Level/GameLevel.h>

Game::Game() {
	levelList.emplace_back(std::make_shared<GameLevel>());

}