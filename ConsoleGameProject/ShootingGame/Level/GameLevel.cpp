#include "GameLevel.h"
#include <Actor/Player.h> // 플레이어 액터추가에 필요
#include <Actor/EnemySpawner.h>

void GameLevel::OnInitialized() 
{
	Level::OnInitialized();

	// 플레이어 액터 추가
	SpawnActor<Player>();

	// 적 생성기 액터 추가
	SpawnActor<EnemySpawner>();
}