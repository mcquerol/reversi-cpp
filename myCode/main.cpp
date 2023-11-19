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


//TODO finalize the main.cpp
//TODO finish replacing the rows and cols with the constants
//TODO add a #define for the outofbounds and replace each instance with the macro name
//TODO add some kind of tie condition (no more spaces left in the board or somethign)
//TODO verify the 2ndclass cpp and h files
//TODO generate doxygen and verify the website and change the title of the website to REVERSI - 1112948


	return 0;
}
