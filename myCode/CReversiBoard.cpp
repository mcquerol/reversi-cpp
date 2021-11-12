/*
 * CReversiBoard.cpp
 *
 *  Created on: 7 Nov 2021
 *      Author: Mateo C. Querol
 */

#include "CReversiBoard.h"
#include "CReversiConsoleView.h"
#include <iostream>

using namespace std;

/*
 * CReversiBoard::CReversiBoard():
 * The constructor initializes a 2d unsigned int array of size 8x8
 * and sets the starting pieces in the middle of the board
 * as per the rules of the game
 *
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 1 2 0 0 0
 * 0 0 0 2 1 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 *
 * 0 = EMPTY
 * 1 = WHITE
 * 2 = BLACK
 *
 */

CReversiBoard::CReversiBoard()
{
	//each colour starts with 2 pieces on the board
	wScore = 2;
	bScore = 2;
	currPlayer = BLACK; // black moves first
	board = new unsigned int*[8];
	for (unsigned int index = 0; index < 8; index++)
	{
		board[index] = new unsigned int[8];
	}
	//set all elements to empty
	for(int r = 0; r < 8; r++)
	{
		for(int c = 0; c < 8; c++)
		{
			board[r][c] = EMPTY;
		}
	}
	//BUT...set the middle 4 pieces respectively
	board[3][3] = WHITE;
	board[3][4] = BLACK;
	board[4][3] = BLACK;
	board[4][4] = WHITE;
}

CReversiBoard::~CReversiBoard()
{
	for(int index = 0; index <8; index++)
	{
		delete [] board[index];
	}
	delete [] board;
}


/**
 * CReversiBoard::checkNeighbors()
 *
 * This method checks the surrounding array elements
 * of non empty elements and assigns them as POSSIBLE
 * this indicates where the player can set the next marker
 */
void CReversiBoard::checkNeighbors(unsigned int color)
{
	for(int r = 0; r < 8; r++)
	{
		for(int c = 0; c < 8; c++)
		{
			if(board[r][c] == EMPTY)
			{
				// don't care if position is empty
				continue;
			}
			if(board[r][c] == POSSIBLE)
			{
				// position already set, don't care
				continue;
			}

			//switch player prespective

			if (currPlayer == WHITE)
			{
				color = BLACK;
			}
			if (currPlayer == BLACK)
			{
				color = WHITE;
			}

			//only show the possible (adjacent) moves
			if (board[r][c] == color)
			{
				//down
				if(board[r+1][c] == EMPTY)
				{
					board[r+1][c] = POSSIBLE;
				}

				//up
				if(board[r-1][c] == EMPTY)
				{
					board[r-1][c] = POSSIBLE;
				}

				//left
				if(board[r][c-1] == EMPTY)
				{
					board[r][c-1] = POSSIBLE;
				}

				//right
				if(board[r][c+1] == EMPTY)
				{
					board[r][c+1] = POSSIBLE;
				}
			}
		}
	}
}

/**
 * CReversiBoard::isLegalMove()
 *
 * Check if a move is possible AND if it is out of bounds
 * INPUT: x, y (user input)
 * OUTPUT: bool (true/false)
 */
bool CReversiBoard::isLegalMove(unsigned int x, unsigned int y)
{
	return 	(board[x][y] == POSSIBLE && (x > 0 && x < 9 && y > 0 && y < 9));
}

/**
 * CReversiBoard::setPiece()
 *
 * set the currPlayer's color at position x,y
 * if it can be placed there
 *
 * INPUT: x, y,(user input) and currPlayer
 * OUTPUT: void
 */
void CReversiBoard::setPiece(unsigned int currPlayer, unsigned int x, unsigned int y)
{
	board[x][y] = currPlayer;
	if(currPlayer == WHITE)
	{
		wScore++;
	}
	if(currPlayer == BLACK)
	{
		bScore++;
	}

}

/**
 * CReversiBoard::flipLine()
 *
 * called by CReversiBoard::flip(), this method checks if the
 * row and col + respective deltas is the opponent player, if yes then return true
 * This is done one "flip" at a time but it is a recursive function
 * so it this method keeps calling itself until the pieces in a line have been flipped
 *
 * INPUT: r, c, (user input) dr, dc, (direction constants) and currPlayer
 * OUTPUT: bool (true/false)
 */
bool CReversiBoard::flipLine(unsigned int dr, unsigned int dc, unsigned int r, unsigned int c, unsigned int currPlayer)
{
	//check for out of bounds
	if (r < 0 || r > 7 || c < 0 || c > 7)
	{
		return false;
	}
	//check for empty
	if (board[r+dr][c+dc]== EMPTY)
	{
		return false;
	}
	if (board[r+dr][c+dc] !=this->currPlayer)
	{
		if(flipLine(dr,dc,r+dr,c+dc,this->currPlayer))
		{
			board[r+dr][c+dc] = this->currPlayer;
			//increment score
			if(currPlayer == WHITE)
			{
				wScore++;
				bScore--;
			}
			if(currPlayer == BLACK)
			{
				bScore++;
				wScore--;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/**
 * CReversiBoard::flip()
 *
 * this method is called by the CReversiBoard::Play() method passing input parameters x and y
 * (given by the user). It recursively calls the CReversiBoard::flipLine() method with different delta values
 * This is to check all 8 directions for possible flips
 *
 * INPUT: x, y (user input)
 * OUTPUT: void
 */
void CReversiBoard::flip(unsigned int x, unsigned int y)
{
	flipLine(-1,0,x,y,this->currPlayer); //up
	flipLine(1,0,x,y,this->currPlayer); //down
	flipLine(0,-1,x,y,this->currPlayer); //left
	flipLine(0,1,x,y,this->currPlayer); //right

	flipLine(-1,-1,x,y,this->currPlayer); //top-left
	flipLine(-1,1,x,y,this->currPlayer); //top-right
	flipLine(1,-1,x,y,this->currPlayer); //bottom-left
	flipLine(1,1,x,y,this->currPlayer); //bottom-right
}

/**
 * CReversiBoard::isGameOver()
 *
 * Checks if the game is over by the score of each player,
 * if white's score is 0 then black wins and if black's score is 0 white wins
 * This is checked in the main superloop after each player has set a marker
 * INPUT: void
 * OUTPUT: 1 (black wins), 2 (white wins), 0 (game continues)
 */
int CReversiBoard::isGameOver()
{
	if(wScore == 0) // black wins
	{
		return 1;
	}
	else if(bScore == 0) // white wins
	{
		return 2;
	}
	else
	{
		return 0; // game continues
	}
}

/**
 * CReversiBoard::switchPlayer()
 *
 * This method changes the class attribute from
 * WHITE to BLACK or vice versa
 *
 * INPUT: void
 * OUTPUT: void
 */
void CReversiBoard::switchPlayer()
{
	if (currPlayer == WHITE)
	{
		currPlayer = BLACK;
	}
	else if (currPlayer == BLACK)
	{
		currPlayer = WHITE;
	}
}

/**
 * CReversiBoard::play()
 *
 * This method creates a control flow for the reversi game by combining
 * all of the methods from this class to make a 2 player reversi game
 *
 * This method is looped 64 times in main.cpp because there are 64
 * spaces and if no one wins after 64 rounds then the game is a TIE
 *
 * This method calls the CReversiConsoleView class' print function by passing the
 * board array as a pointer
 *
 * INPUT: x, y (user input)
 * OUTPUT: void
 */
void CReversiBoard::play()
{
	CReversiConsoleView screen((unsigned int**)board); //create local screen object
	unsigned int x; //x user input
	unsigned int y; //y user input
	string playerStr;


	if(currPlayer == WHITE)
	{
		playerStr = "WHITE";
	}
	else if(currPlayer == BLACK)
	{
		playerStr = "BLACK";
	}
	checkNeighbors(currPlayer);

	//call the print function passing the player string
	screen.print(playerStr, this->wScore, this->bScore);

	//x,y input validation
	do
	{
		cout <<"enter x and y coordinate (0-8) "<<endl;
		cin >> x;
		cin >> y;
		if (((x<1) || (x>8)) || ((y<1) || (y>8)))
		{
			cout << "INVALID INPUT" << endl;
		}

	}while (((x<=1) || (x>=8)) || ((y<=1) || (y>=8)));
	setPiece(currPlayer, y-1, x-1); // x and y - 1 because arrays are 0 indexed
	flip(y-1,x-1);
	resetBoard();
	switchPlayer();
}

/**
 * CReversiBoard::play()
 *
 * This method loops through the entire board and if it finds a POSSIBLE
 * element, it clears it. This is to reset the prespective when switching players
 *
 * INPUT: void
 * OUTPUT: void
 */
void CReversiBoard::resetBoard()
{
  	for(int r = 0; r < 8; r++)
	{
  		for (int c = 0; c < 8; c++)
  		{
  	  		if(board[r][c] == POSSIBLE)
  	  		{
  	  			board[r][c] = EMPTY;
  	  		}
  		}
	}
}
