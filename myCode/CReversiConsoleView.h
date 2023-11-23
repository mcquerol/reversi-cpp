#ifndef CREVERSICONSOLEVIEW_H_
#define CREVERSICONSOLEVIEW_H_
#include "CReversiBoard.h"
#include <iostream>

/**
 * @class CReversiConsoleView
 * @brief Handles the console output for the Reversi game.
 *
 * The class is responsible for printing the game board and scores to the console.
 */
class CReversiConsoleView
{
public:
    /**
     * @brief Constructor for CReversiConsoleView class.
     * @param board The double pointer to the game board.
     */
    CReversiConsoleView(CReversiBoard::eStates **board);

    /**
     * @brief Destructor for CReversiConsoleView class.
     */
    ~CReversiConsoleView();

    /**
     * @brief Prints the current state of the game board along with scores.
     * @param playerStr String representation of the current player.
     * @param wScore White player's score.
     * @param bScore Black player's score.
     */
    void print(std::string playerStr, int wScore, int bScore) const;

private:
	CReversiBoard::eStates **m_pBoard; /**< Double pointer to the game board. */
};

#endif /* CREVERSICONSOLEVIEW_H_ */
