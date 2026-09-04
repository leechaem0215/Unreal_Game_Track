#include <Game/Game.h>
#include <Engine/Engine.h>
#include <Level/GameLevel.h>

int main(){
	SetConsoleTitleA("BoxHead");

	Craft::Engine engine;
	engine.AddNewLevel<GameLevel>();
	engine.Run();

	//Game game;
	//game.Run();
}