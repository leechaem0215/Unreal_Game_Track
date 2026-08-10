#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class EnemySpawner : public Craft::Actor
{
	TYPE_DECLARATIONS(EnemySpawner, Actor)

public:
	EnemySpawner();

private:
	virtual void Tick(float deltaTime) override;

	/// <summary>
	/// 적 생성함수
	/// </summary>
	void SpawnEnemy();

private:
	// 타이머
	Timer timer;
};


