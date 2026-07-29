#pragma once
// #include "Weapon.h"

// 전방선언
// 1. 컴파일 시간 단축
// 2. 헤더 순환 참조 방지.

// 전방선언은 포인터 타입에만 사용가능
// 왜? 일반변수로하면 타입이 메모리를 얼마나 먹고있어야하나 알고있어야한다.
// 타입 지정은 메모리 크기 지정임
// 왜 포인터는 될까? 포인터의 크기 8바이트 고정이다.

class Weapon; // 전방선언

// ctrl+k+o
class Player
{
public:
	Player();
	~Player();

private:
	// Weapon 변수
	//class Weapon* weapon = nullptr; // 전방 선언을 함으로써 include 하지 않아도 됌.
	// 근데 전방 선언은 오타를 못잡음. WeaponA* 와 같이 오타 발생하면.
	Weapon* weapon = nullptr;
	
};