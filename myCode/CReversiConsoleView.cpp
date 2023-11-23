#include "CReversiConsoleView.h"
#include "CReversiBoard.h"

#include <iostream>

/**
 * @brief Constructor for CReversiConsoleView class.
 * @param board The double pointer to the game board.
 */
CReversiConsoleView::CReversiConsoleView(CReversiBoard::eStates **board)
{
	m_pBoard = board;
}

/**
 * @brief Destructor for CReversiConsoleView class.
 */
CReversiConsoleView::~CReversiConsoleView()
{

}

/**
 * @brief Prints the current state of the game board along with scores.
 * @param playerStr String representation of the current player.
 * @param wScore White player's score.
 * @param bScore Black player's score.
 */
void CReversiConsoleView::print(std::string playerStr, int wScore, int bScore) const
{

	std::cout << "-----------------" << std::endl;
	std::cout << playerStr << "'s turn" << std::endl;
  	std::cout << "-----------------" << std::endl;
  	std::cout << " ";
	for(int col = 0; col < NO_COLS; col++)
	{
		std::cout << " " << col + 1; //column numbers
	}
	std::cout << std::endl;
  	for(int row = 0; row < NO_ROWS; row++)
	{
  		std::cout << row + 1 << " "; // row numbers
		for(int col = 0; col < NO_COLS; col++)
	    {
			switch(m_pBoard[row][col])
			{
			case CReversiBoard::eStates::EMPTY:
				std::cout << '-' << " ";
				break;
			case CReversiBoard::eStates::WHITE:
				std::cout << 'W' << " ";
				break;
			case CReversiBoard::eStates::BLACK:
				std::cout << 'B' << " ";
				break;
			case CReversiBoard::eStates::POSSIBLE:
				std::cout << '*' << " ";
				break;
			default:
				std::cout << "NULL" << " "; //NULL pointer
			}
	    }
		std::cout << std::endl;
	}
  	//output scores
  	std::cout << "-----------------" << std::endl;
  	std::cout << "BLACK's score: " << bScore << std::endl;
  	std::cout << "WHITE's score: " << wScore << std::endl;
  	std::cout << "-----------------" << std::endl;
}
