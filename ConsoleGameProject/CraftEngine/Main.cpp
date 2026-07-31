#include <iostream>
#include <Engine/Engine.h> // 이거 사용하려면 속성에서 c++ 일반 들어가서 프로젝트 경로 설정해줘야함
// "" 와 <> - <>은 현재경로는 안 찾음, ""는 현재경로도 찾음 (검색범위가 넓음, 근데 하지말라함)
#include <Level/TestLevel.h>

int main() 
{
	// 엔진 객체 생성 및 실행
	Craft::Engine engine;
	engine.AddNewLevel<TestLevel>();
	engine.Run();
}