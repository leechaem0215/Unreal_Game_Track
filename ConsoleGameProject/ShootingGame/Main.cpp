#include <Engine/Engine.h>
#include <Level/GameLevel.h>

int main() 
{
	// 엔진 객체 생성 및 실행
	Craft::Engine engine; // 엔진객체 만들어주고
	engine.AddNewLevel<GameLevel>(); // 시작 레벨 추가 // 원래 직렬화 기능을 이용해야하는데 여기서는 뺌
	engine.Run(); // 런
}