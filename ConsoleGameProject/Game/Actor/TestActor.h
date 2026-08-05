#pragma once

#include <Actor/Actor.h>

// 테스트 액터
class TestActor : public Craft::Actor
{
public:
	virtual void Tick(float deltaTime) override;
};

// WASD / 방향키 이동처리
// @Temp : 프레임 시간 고려는 나중에
if (Input::Get().GetKey(VK_LEFT) && position.x >0) {
	position.x -= 1;
}
if (Input::Get().GetKey(VK_RIGHT) && position.x < 39) { // 39는 예시 // 39보다 작으면 증가처리
	position.x += 1;
}
if (Input::Get().GetKey(VK_UP) && position.y > 0) {
	position.y -= 1;
}
if (Input::Get().GetKey(VK_DOWN) && position.y < 24) { // 콘솔은 세로가 더 길다
	position.y += 1; // 콘솔좌표계는 내려갈때 y가 + 이다.
}