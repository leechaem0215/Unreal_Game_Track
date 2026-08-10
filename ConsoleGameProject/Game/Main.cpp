//#include <Engine/Engine.h>
//#include <Level/TestLevel.h>
#include <Game/Game.h>
#include <Level/GameLevel.h>

int main()
{
	//Craft::Engine engine;
	////engine.AddNewLevel<TestLevel>();
	//engine.AddNewLevel<GameLevel>();
	//engine.Run();

	// 창 제목 설정
	SetConsoleTitleA("Sokoban Game");

	// 엔진으로 만들던거 게임으로 바꿀거임
	// 게임 객체 만들고 게임의 run 실행
	Game game;
	game.Run();
}