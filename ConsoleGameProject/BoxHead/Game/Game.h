#pragma once

#include <Engine/Engine.h>
#include <vector>

class Game : public Craft::Engine
{
public:
	Game();
	~Game() = default;

private:
	std::vector<std::shared_ptr<Craft::Level>> levelList;
};

