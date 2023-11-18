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


void CReversiBoard::checkNeighbors(unsigned int currPlayer)
{
    // Iterate through the entire board
    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
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
                    if (row < 0 || row >= 8 || col < 0 || col >= 8)
                    {
                        continue;
                    }

                    // If the neighbor is of the opposite color, continue checking in that direction
                    if (board[row][col] != EMPTY && board[row][col] != currPlayer)
                    {
                        // Continue in the direction until an empty space or out-of-bounds is reached
                        while (row >= 0 && row < 8 && col >= 0 && col < 8 && board[row][col] == (currPlayer == WHITE ? BLACK : WHITE))
                        {
                            row += dr;
                            col += dc;
                        }

                        // If the final position is within bounds and empty, mark it as POSSIBLE
                        if (row >= 0 && row < 8 && col >= 0 && col < 8 && board[row][col] == EMPTY)
                        {
                            board[row][col] = POSSIBLE;
                        }
                    }
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
bool CReversiBoard::isLegalMove(unsigned int row, unsigned int col)
{
	return (board[row][col] == 3 && (row >= 0 && row < 8 && col >= 0 && col < 8));
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
void CReversiBoard::setPiece(unsigned int player, unsigned int row, unsigned int col)
{
    if (board[row][col] == POSSIBLE)
    {
        board[row][col] = player;  // Set the piece on the board
        flipAllDirections(row, col);  // Flip pieces in all directions
    }
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

void CReversiBoard::flip(int row, int col, int dr, int dc) {
    int r = row + dr;
    int c = col + dc;

    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
        if (board[r][c] == EMPTY) {
            break;  // Stop flipping when an empty space is encountered
        } else if (board[r][c] == currPlayer) {
            // Flip the pieces only when the loop encounters the same color
            while (r != row || c != col) {
                r -= dr;
                c -= dc;
                board[r][c] = currPlayer;  // Flip the piece
            }
            break;
        }
        r += dr;
        c += dc;
    }
}


void CReversiBoard::flipAllDirections(int row, int col) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;  // Skip the current position
            flip(row, col, dr, dc);  // Flip pieces in the specified direction
        }
    }
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

	currPlayer = (currPlayer == WHITE) ? BLACK : WHITE;
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
		if(!isLegalMove(x-1,y-1))
		{
			cout << "INVALID INPUT" << endl;
		}

	}while (!isLegalMove(x-1,y-1));

	setPiece(currPlayer, y - 1, x - 1); // x and y - 1 because arrays are 0 indexed
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
