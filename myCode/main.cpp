#include "CReversiBoard.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>


using namespace std;


int main (void)
{

	CReversiBoard game;
	cout << "REVERSI GAME" << endl;
	for (int round = 0; round < 64; round++)
	{
		game.play(); //start the game
		if(game.isGameOver() == 1)
		{
			cout << "BLACK WINS!!" << endl;
		}
		else if (game.isGameOver() == 2)
		{
			cout << "WHITE WINS!!" << endl;
		}
		else
		{
			continue;
		}
	}
	cout << "TIE GAME" << endl;


//TODO finish the rest of the loop and implement the other class

	return 0;
}
