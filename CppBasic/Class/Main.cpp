#include <iostream>

class Player
{
	// Manager 클래스를 friend로 선언
	friend class Manager;

public:
	Player() = default;
	~Player() = default;
public:
	void SetXY(int newX, int newY) {
		x = newX;
		y = newY;
	}

	// friend 선언
	friend void SetPosition(Player& player, int newX, int newY);

private:
	int x = 0;
	int y = 0;
};

class Manager {
public:
	Manager(Player* const newPlayer)
		: player(newPlayer)
	{

	}
	void Test() {
		player->x = 30;
		player->y = 60;
	}
private:
	Player* player = nullptr;
};


// Player의 x,y 위치를 설정하는 전역 함수.
void SetPosition(Player& player, int newX, int newY) {
	player.SetXY(newX, newY); // 이게 맞음 아래 2개는 해보려고 하는것.
	//player.x = newX;
	//player.y = newY;

	//----------------------------------------------------------------//
	// friend void SetPosition(Player& player, int newX, int newY); 하면 빨간 줄 사라짐
	// 친구로 등록하면 private 접근이 가능하다.
	// 강력한 키워드
	player.x = newX;
	player.y = newY;

}

int main() {
	// 객체 포인터 배열
	const int length = 5;
	Player* players[length] = {};

	// 객체 생성
	for (int ix = 0; ix < length; ++ix) {
		players[ix] = new Player();
	}

	// 사용
	SetPosition(*players[0], 3, 5);

	Manager manager(players[1]);
	manager.Test();

	// 객체 소멸 및 null
	for (Player*& player : players) {
		delete player;
		player = nullptr;
	}

	std::cin.get();
}