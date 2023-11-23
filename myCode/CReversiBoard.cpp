#include "CReversiBoard.h"
#include "CReversiConsoleView.h"
#include <iostream>

/**
 * @brief Constructor for the CReversiBoard class.
 * Initializes the game m_pBoard and sets the starting pieces.
 */
CReversiBoard::CReversiBoard()
{

	//the game starts with 2 pieces of each color
	m_row = 0; // initial value of row
	m_col = 0; // initial value of col
	m_wScore = 2;
	m_bScore = 2;
	m_currPlayer = BLACK; // black moves first

	m_pBoard = new eStates*[NO_ROWS];
	for (int index = 0; index < NO_ROWS; index++)
	{
		m_pBoard[index] = new eStates[NO_COLS];
	}

	//set all elements to empty
	for(int r = 0; r < NO_ROWS; r++)
	{
		for(int c = 0; c < NO_COLS; c++)
		{
			m_pBoard[r][c] = EMPTY;
		}
	}

	//Starting positions for Reversi
	m_pBoard[3][3] = WHITE;
	m_pBoard[3][4] = BLACK;
	m_pBoard[4][3] = BLACK;
	m_pBoard[4][4] = WHITE;

}

/**
 * @brief Destructor for the CReversiBoard class.
 * Frees the memory allocated for the game m_pBoard.
 */
CReversiBoard::~CReversiBoard()
{
	for(int index = 0; index < NO_ROWS; index++)
	{
		delete [] m_pBoard[index];
	}
	delete [] m_pBoard;
}

/**
 * @brief Checks if the given row and column are out of bounds.
 * @param row The row index.
 * @param col The column index.
 * @return True if out of bounds, false otherwise.
 */
bool CReversiBoard::isOutOfBounds(int row, int col) const
{
    return (row < 0 || row >= NO_ROWS || col < 0 || col >= NO_COLS);
}

/**
 * @brief Checks the neighbors of each m_pBoard position and marks possible moves.
 */
void CReversiBoard::checkNeighbors()
{
    // Iterate through the entire m_pBoard
    for (int r = 0; r < NO_ROWS; r++)
    {
        for (int c = 0; c < NO_COLS; c++)
        {
            /* skip iteration if:
             * empty spaces
             * positions that are already marked as POSSIBLE
             * positions that don't match the current player's color
             */
            if (m_pBoard[r][c] == EMPTY || m_pBoard[r][c] == POSSIBLE || m_pBoard[r][c] != m_currPlayer)
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
                    if (isOutOfBounds(row, col))
                    {
                        continue;
                    }

                    // If the neighbor is of the opposite color, continue checking in that direction
                    if (m_pBoard[row][col] != EMPTY && m_pBoard[row][col] != m_currPlayer)
                    {
                        // Continue in the direction until an empty space or out-of-bounds is reached
                        while (!isOutOfBounds(row, col) && m_pBoard[row][col] == (m_currPlayer == WHITE ? BLACK : WHITE))
                        {
                            row += dr;
                            col += dc;
                        }

                        // If the final position is within bounds and empty, mark it as POSSIBLE
                        if (!isOutOfBounds(row, col) && m_pBoard[row][col] == EMPTY)
                        {
                            m_pBoard[row][col] = POSSIBLE;
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Checks if the current move is legal.
 * @return True if legal, false otherwise.
 */
bool CReversiBoard::isLegalMove()
{
    // Check if the initial move coordinates are within bounds
    if (isOutOfBounds(m_row, m_col))
    {
        return false;
    }

    return (m_pBoard[m_col][m_row] == POSSIBLE);
}

/**
 * @brief Sets the current player's piece on the m_pBoard and flips pieces accordingly.
 */
void CReversiBoard::setPiece()
{
    if (m_pBoard[m_col][m_row] == POSSIBLE)
    {
        m_pBoard[m_col][m_row] = m_currPlayer;  // Set the piece on the m_pBoard

        flip();  // Flip pieces in all directions

        (m_currPlayer == WHITE) ? m_wScore++ : m_bScore++; //increase the score by 1 (user piece)
    }
}

/**
 * @brief Flips pieces in all directions based on the current move.
 */
void CReversiBoard::flip()
{
    for (int dr = -1; dr <= 1; ++dr)
    {
        for (int dc = -1; dc <= 1; ++dc)
        {
            if (dr == 0 && dc == 0)
            {
                continue;  // Skip the current position
            }

            int r = m_col + dr;
            int c = m_row + dc;
            int flippedCount = 0;

            while (!isOutOfBounds(r,c))
            {
                if (m_pBoard[r][c] == EMPTY)
                {
                    break;  // Break if an empty space is encountered
                }

                else if (m_pBoard[r][c] == m_currPlayer)
                {
                    // Flip the pieces only if the loop encountered the same color
                    while (flippedCount > 0)
                    {
                        r -= dr;
                        c -= dc;
                        m_pBoard[r][c] = m_currPlayer;  // Flip the piece

                        // Update scores based on the current player
                        if (m_currPlayer == WHITE)
                        {
                        	m_wScore++;
                        	m_bScore--;
                        }
                        else
                        {
                        	m_bScore++;
                        	m_wScore--;
                        }

                        flippedCount--;
                    }

                    break;  // Break out of the while loop
                }
                else
                {
                    // Continue flipping in the same direction
                    r += dr;
                    c += dc;
                    flippedCount++;
                }
            }
        }
    }
}

/**
 * @brief Switches the current player.
 */
void CReversiBoard::switchPlayer()
{
	m_currPlayer = (m_currPlayer == WHITE) ? BLACK : WHITE;
}

/**
 * @brief Resets the m_pBoard by clearing POSSIBLE markers.
 */
void CReversiBoard::resetBoard()
{
  	for(int r = 0; r < NO_ROWS; r++)
	{
  		for (int c = 0; c < NO_COLS; c++)
  		{
  	  		if(m_pBoard[r][c] == POSSIBLE)
  	  		{
  	  			m_pBoard[r][c] = EMPTY;
  	  		}
  		}
	}
}

/**
 * @brief Game logic per turn including user input validation
 */
void CReversiBoard::play()
{

	CReversiConsoleView screen((eStates**)m_pBoard); //create local screen object

	std::string playerStr;

	playerStr = (m_currPlayer == WHITE) ? "WHITE" : "BLACK"; //set player string for output

	checkNeighbors();

	//call the print function passing the player string
	screen.print(playerStr, m_wScore, m_bScore);

	//x,y input validation
	do
	{
		std::cout << "enter x and y coordinate (1-8) "<< std::endl;
		std::cin >> m_row;
		std::cin >> m_col;

		// row and col are - 1 because arrays are 0 indexed
		m_row--;
		m_col--;

		if(!isLegalMove())
		{
			std::cerr << "INVALID MOVE" << std::endl;
		}

	}while (!isLegalMove());

	setPiece();
	resetBoard();
	switchPlayer();

}

/**
 * @brief Checks if the game is over and returns the winner.
 * @return 0 for ongoing, 1 if white wins, 2 if black wins, 3 if it is a tie
 */
int CReversiBoard::isGameOver() const
{
	//calculate # of empty spaces on the board
	int emptySpaces = (NO_ROWS * NO_COLS) - m_wScore - m_bScore;

    if (m_wScore == 0 || m_bScore == 0)
    {
		if (m_wScore > m_bScore)
		{
			return 1;
		}
		else if (m_bScore > m_wScore)
		{
			return 2;
		}
	    else if (emptySpaces == 0)
	    {
	        return 3; // All spaces are filled, it's a tie
	    }
    }
    else if (emptySpaces == 0)
    {
        return 3; // All spaces are filled, it's a tie
    }

    return 0; // continue game
}
