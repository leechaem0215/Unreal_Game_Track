#pragma once

#include <Level/Level.h>
#include <string>

class GameLevel : public Craft::Level
{
	TYPE_DECLARATIONS(GameLevel, Level);

public:
	// 플레이어 이동 가능한 위치인지
	bool CanMove(
		const Craft::Vector2& playerPosition,
		const Craft::Vector2& nextPosition
	);

private:
	virtual void OnInitialized() override;

	virtual void Draw() override;

	void LoadMap(const std::string& filename);

private:
	int score = 0;
};

