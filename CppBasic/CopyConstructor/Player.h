#pragma once
class Player
{
public:
	Player();
	Player(const char* inName);
	// 복사 생성자
	Player(const Player& other);

	~Player();

	// 대입(=) 연산자 오버로딩
	// 연산자->연산자를 이름으로 갖는 함수.
	Player& operator = (const Player& other);

	// Getter (값 반환하는 함수)
	inline const char* GetName() const { return name; }
private:
	char* name = nullptr;
};
