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
 * 0 0 0 3 0 0 0 0
 * 0 0 3 1 2 0 0 0
 * 0 0 0 2 1 3 0 0
 * 0 0 0 0 3 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 *
 * 0 = EMPTY
 * 1 = WHITE
 * 2 = BLACK
 * 3 = POSSIBLE
 *
 */

CReversiBoard::CReversiBoard()
{
	//the game starts with 2 pieces of each color
	wScore = 2;
	bScore = 2;
	currPlayer = BLACK; // black moves first

	board = new int*[NO_ROWS];
	for (int index = 0; index < NO_ROWS; index++)
	{
		board[index] = new int[NO_COLS];
	}

	//set all elements to empty
	for(int r = 0; r < NO_ROWS; r++)
	{
		for(int c = 0; c < NO_COLS; c++)
		{
			board[r][c] = EMPTY;
		}
	}

	//Starting positions for Reversi
	board[3][3] = WHITE;
	board[3][4] = BLACK;
	board[4][3] = BLACK;
	board[4][4] = WHITE;

}

CReversiBoard::~CReversiBoard()
{
	for(int index = 0; index < NO_ROWS; index++)
	{
		delete [] board[index];
	}
	delete [] board;
}

void CReversiBoard::checkNeighbors()
{
    // Iterate through the entire board
    for (int r = 0; r < NO_ROWS; r++)
    {
        for (int c = 0; c < NO_COLS; c++)
        {
            // Skip empty spaces
            if (board[r][c] == EMPTY)
            {
                continue;
            }

            // Skip positions that are already marked as POSSIBLE
            if (board[r][c] == POSSIBLE)
            {
                continue;
            }

            // Skip positions that don't match the current player's color
            if (board[r][c] != currPlayer)
            {
                continue;
            }

            // Check all 8 directions
            for (int dr = -1; dr <= 1; ++dr)
            {
                for (int dc = -1; dc <= 1; ++dc)
                {
                    // Skip the case where both delta values are zero (current position)
                    if (dr == 0 && dc == 0)
                    {
                        continue;
                    }

                    // Check the neighbor in the current direction
                    int row = r + dr;
                    int col = c + dc;

                    // Skip out-of-bounds positions
                    if (OUT_OF_BOUNDS(row, col))
                    {
                        continue;
                    }

                    // If the neighbor is of the opposite color, continue checking in that direction
                    if (board[row][col] != EMPTY && board[row][col] != currPlayer)
                    {
                        // Continue in the direction until an empty space or out-of-bounds is reached
                        while (!OUT_OF_BOUNDS(row, col) && board[row][col] == (currPlayer == WHITE ? BLACK : WHITE))
                        {
                            row += dr;
                            col += dc;
                        }

                        // If the final position is within bounds and empty, mark it as POSSIBLE
                        if (!OUT_OF_BOUNDS(row, col) && board[row][col] == EMPTY)
                        {
                            board[row][col] = POSSIBLE;
                        }
                    }
                }
            }
        }
    }
}

bool CReversiBoard::isLegalMove(int row, int col)
{
	return (board[col][row] == POSSIBLE && (!OUT_OF_BOUNDS(row, col)));
}

void CReversiBoard::setPiece(int player, int row, int col)
{
    if (board[row][col] == POSSIBLE)
    {
        board[row][col] = player;  // Set the piece on the board

        if (currPlayer == WHITE) { //increment the score by 1
            wScore++;
        } else {
            bScore++;
        }
        flip(row, col);  // Flip pieces in all directions
    }
}

void CReversiBoard::flip(int row, int col) {
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0)
			{
            	continue;  // Skip the current position
			}

            int r = row + dr;
            int c = col + dc;
            int flippedCount = 0;

            while (!OUT_OF_BOUNDS(r, c)) {
                if (board[r][c] == EMPTY) {
                    break;
                } else if (board[r][c] == currPlayer) {
                    // Flip the pieces only if the loop encountered the same color
                    while (flippedCount > 0) {
                        r -= dr;
                        c -= dc;
                        board[r][c] = currPlayer;  // Flip the piece

                        // Update scores based on the current player
                        if (currPlayer == WHITE) {
                            wScore++;
                            bScore--;
                        } else {
                            bScore++;
                            wScore--;
                        }

                        flippedCount--;
                    }
                    break;
                } else {
                    // Continue flipping in the same direction
                    r += dr;
                    c += dc;
                    flippedCount++;
                }
            }
        }
    }
}

int CReversiBoard::isGameOver()
{
	return (wScore == 0) ? WHITE : (bScore == 0) ? BLACK : 0;
}

void CReversiBoard::switchPlayer()
{
	currPlayer = (currPlayer == WHITE) ? BLACK : WHITE;
}

void CReversiBoard::play()
{
	CReversiConsoleView screen((int**)board); //create local screen object
	unsigned int x; //x user input
	unsigned int y; //y user input
	string playerStr;

	playerStr = (currPlayer == WHITE) ? "WHITE" : "BLACK"; //set player string for output

	checkNeighbors();

	//call the print function passing the player string
	screen.print(playerStr, wScore, bScore);

	//x,y input validation
	do
	{
		cout << "enter x and y coordinate (1-8) "<< endl;
		cin >> x;
		cin >> y;
		if(!isLegalMove(x - 1,y - 1))
		{
			cout << "INVALID MOVE" << endl;
		}

	}while (!isLegalMove(x - 1,y - 1));

	setPiece(currPlayer, y - 1, x - 1); // x and y are - 1 because arrays are 0 indexed
	resetBoard();
	switchPlayer();


}

void CReversiBoard::resetBoard()
{
  	for(int r = 0; r < NO_ROWS; r++)
	{
  		for (int c = 0; c < NO_COLS; c++)
  		{
  	  		if(board[r][c] == POSSIBLE)
  	  		{
  	  			board[r][c] = EMPTY;
  	  		}
  		}
	}
}
