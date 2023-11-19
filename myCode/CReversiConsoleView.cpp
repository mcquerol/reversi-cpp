/*
 * CReversiConsoleView.cpp
 *
 *  Created on: 8 Nov 2021
 *      Author: Mateo C. Querol
 */

#include "CReversiConsoleView.h"
#include "CReversiBoard.h"
#include <iostream>

using namespace std;

CReversiConsoleView::CReversiConsoleView(int **board)
{
	boardptr = board;
}

CReversiConsoleView::~CReversiConsoleView()
{

}

/** CReversiConsoleView::print()
 *
 * This method prints the board passed as a double pointer from the
 * CReversiBoard class. It also prints the current player's turn
 * and makes the board look pretty
 */
void CReversiConsoleView::print(std::string playerStr, int wScore, int bScore)
{
	cout << "-----------------" << endl;
	cout << playerStr << "'s turn" << endl;
  	cout << "-----------------" << endl;
  	cout << " ";
	for(int col = 0; col < NO_COLS; col++)
	{
		cout << " " << col + 1; //column numbers
	}
	cout << endl;
  	for(int row = 0; row < NO_ROWS; row++)
	{
  		cout << row + 1 << " "; // row numbers
		for(int col = 0; col < NO_COLS; col++)
	    {
			switch(boardptr[row][col])
			{
			case 0:
				cout << '-' << " ";
				break;
			case 1:
				cout << 'W' << " ";
				break;
			case 2:
				cout << 'B' << " ";
				break;
			case 3:
				cout << '*' << " ";
			}
	    }
		cout << endl;
	}
  	//output scores
  	cout << "-----------------" << endl;
  	cout << "BLACK's score: " << bScore << endl;
  	cout << "WHITE's score: " << wScore << endl;
  	cout << "-----------------" << endl;
}
