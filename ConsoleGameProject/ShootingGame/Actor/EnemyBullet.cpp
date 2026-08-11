#include "EnemyBullet.h"
#include <Engine/Engine.h>

using namespace Craft;
EnemyBullet::EnemyBullet(const Vector2& position, float moveSpeed)
	:Actor("#", position, Color::Red),
	moveSpeed(moveSpeed), yPosition(static_cast<float>(position.y))
{

}

// 적의 탄약은 위에서 아래로 내려가야하니까 y 위치를 더해주면 된다.
void EnemyBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// y 위치 업데이트 (아래로 이동 처리).
	// 빠르기 * 시간값임 (1은 생략)
	yPosition += moveSpeed * deltaTime;

	// y 로 이동해서 화면 아래 끝지점 도달하면 제거
	// 좌표 검사.
	if (yPosition >= Engine::Get().GetHeight() -1) // 아래쪽끝에 도달했는지 봄 -1 넣어야함
	{
		Destroy();
		return;
	}

	// 화면 밖에 벗어나서 레벨에 존재할 이유가 없다
	// 위치 설정.
	SetPosition(Vector2(
		GetPosition().x, static_cast<int>(yPosition)
	));

	// x는 기존 위치와 동일하고 y는 yPosition
	// float 를 형변환해서 위치 설정할거임

}
