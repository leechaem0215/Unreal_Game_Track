#include "GameLevel.h"
#include <Actor/Ground.h>
#include <Actor/Player.h>
#include <Actor/Wall.h>
#include <Actor/Zombie.h>


#include <cassert>

using namespace Craft;
bool GameLevel::CanMove(const Craft::Vector2& playerPosition, const Craft::Vector2& nextPosition) {
	std::vector<std::shared_ptr<Actor>> boxList;

	for (const std::shared_ptr<Actor>& actor : actorList){
		if (actor->GetPosition() == nextPosition) {
			if (actor->IsTypeOf<Wall>()) {
				return false;
			}

			return true;
		}
	}
	return false;
}



void GameLevel::OnInitialized() {
	Level::OnInitialized();

	LoadMap("Stage1.txt");
}

void GameLevel::Draw() {
	Level::Draw();
}

void GameLevel::LoadMap(const std::string& filename) {
	std::string path = std::string("../Assets/") + filename;
	
	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rt");

	if (!file)
	{
		assert(false && "failed to open a BoxHead file.");
		return;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	rewind(file);

	char* buffer = new char[fileSize] {};

	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	assert(readSize > 0 && "No data is in the stage file.");

	int index = 0;

	Vector2 position; // 액터 생성에 사용될 위치
	while (true) {
		if (index >= fileSize) {
			break;
		}
		char mapCharacter = buffer[index];

		index++;

		if (mapCharacter == '\n') {
			++position.y;
			position.x = 0;
			continue;
		}
		switch (mapCharacter) {
		case '#':
			SpawnActor<Wall>(position);
			break;
		case '.':
			SpawnActor<Ground>(position);
			break;
	
		case 'p':
			SpawnActor<Ground>(position);
			SpawnActor<Player>(position);
			break;
		case 'z':
			SpawnActor<Ground>(position);
			SpawnActor<Zombie>(position);
			break;

			position.x++;
		}
	}
	delete[] buffer;
	buffer = nullptr;

	fclose(file);
	file = nullptr;
}