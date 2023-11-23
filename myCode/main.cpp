#include "CReversiBoard.h"

#include <iostream>
int main (void)
{

	CReversiBoard game;
	std::cout << "REVERSI GAME" << std::endl;
	while(game.isGameOver() == 0)
	{
		game.play(); //start the game
		switch(game.isGameOver())
		{
			case 0: //game not over
				continue;
			case 1: //white wins
				std::cout << "WHITE WINS!!" << std::endl;
				break;
			case 2: //black wins
				std::cout << "BLACK WINS!!" << std::endl;
				break;
			case 3: //time game
				std::cout << "TIE GAME!!" << std::endl;
				break;
			default:
				std::cerr << "ERROR" << std::endl;
				break;
		}
	}

	return 0;
}
