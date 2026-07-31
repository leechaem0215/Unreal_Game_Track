#include "Player.h"
#include <iostream>

int main() {
	//Player* player1  =new Player();
	//Player* player2 = new Player("Ronnie");
	//Player* player3 = new Player(*player2);
	
	Player player1;
	Player player2 = "Ronnie";
	Player player3 = player2;
	Player player4 = player3;

	//delete player1;
	//delete player2;
	//delete player3;
	//std::cin.get();
}