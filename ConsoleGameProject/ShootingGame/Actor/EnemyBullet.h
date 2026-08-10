#pragma once

#include <Actor/Actor.h>

class EnemyBullet : public Craft::Actor // Actor 니까 해줌
{
	TYPE_DECLARATIONS(EnemyBullet, Actor)

public:
	EnemyBullet(
		const Craft::Vector2& position,
		float moveSpeed = 15.0f
	);

private:
	// 이벤트 함수 오버라이드
	virtual void Tick(float deltaTime) override; // 오버라이드 할때는 public 으로 하지 않아도 됌

private:
	// float 기반이랑 이동속도가 필요함
	float moveSpeed = 0.0f;
	// y 위치 처리를 위해 필요
	float yPosition = 0.0f;

};

