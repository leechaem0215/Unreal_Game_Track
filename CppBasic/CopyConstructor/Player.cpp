#include "Player.h"
#include <iostream>

Player::Player() {
	std::cout << "Player() called\n";
}
Player::Player(const char* inName) {
	// 문자열 복사
	size_t length = strlen(inName) + 1;
	name = new char[length]{}; // 공간 확보
	strcpy_s(name, length, inName); // 문자열 복사


	std::cout << "Player(const char* inName) called\n";
}
// 복사 생성자
Player::Player(const Player& other)
	: name(other.name)
{
	// 얕은복사 -> 포인터 주소 값만 복사
	// name = other.name;
	// 깊은 복사 // 접근 한정자
	// 같은 타입 안에서 접근이 가능하다.
	size_t length = strlen(other.name) + 1;
	name = new char[length] {};
	strcpy_s(name, length, other.name);

	// 문자열 복사 처리
	std::cout << "Player((const Player& other) called\n";
}

// new 가 나왔기 때문에 소멸자를 생성
Player::~Player() {
	if (name) {
		delete[] name;
		name = nullptr;
	}
}

Player& Player::operator=(const Player& other)
{
	// 복사 처리
	size_t length = strlen(other.name) + 1;
	name = new char[length] {};
	strcpy_s(name, length, other.name);

	std::cout << "operator=(const Player& other) called\n";
	return *this;
}
