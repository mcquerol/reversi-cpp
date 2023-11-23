#ifndef CREVERSIBOARD_H_
#define CREVERSIBOARD_H_

#define NO_ROWS 8
#define NO_COLS 8

/**
 * @class CReversiBoard
 * @brief Represents the Reversi game board and game logic.
 *
 * 2D array is an array of enum values (int) and looks like this:
 * @verbatim
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 3 0 0 0 0
 * 0 0 3 1 2 0 0 0
 * 0 0 0 2 1 3 0 0
 * 0 0 0 0 3 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * @endverbatim
 *
 * 0 = EMPTY
 * 1 = WHITE
 * 2 = BLACK
 * 3 = POSSIBLE
 *
 * The class manages the game state, player turns, and board manipulation.
 */
class CReversiBoard
{
public:

	/**
	 * @brief Enumeration representing the possible states of a Reversi board cell.
	 */
	enum eStates
	{
	    EMPTY,     /**< Represents an empty cell on the board. */
	    WHITE,     /**< Represents a cell occupied by a white piece. */
	    BLACK,     /**< Represents a cell occupied by a black piece. */
	    POSSIBLE   /**< Represents a cell where a move is currently possible. */
	};

    /**
     * @brief Constructor for CReversiBoard class.
     * Initializes the board and sets starting pieces.
     */
    CReversiBoard();

    /**
     * @brief Destructor for CReversiBoard class.
     * Frees the memory allocated for the board.
     */
    ~CReversiBoard();

    /**
     * @brief Initiates the game loop for Reversi.
     */
    void play();

    /**
     * @brief Checks if the game is over and returns the winner.
     * @return 0 for ongoing, WHITE if white wins, BLACK if black wins.
     */
    int isGameOver() const;

private:

    eStates m_currPlayer; /**< Current player, BLACK or WHITE. */
    int m_wScore; /**< Score for the WHITE player. */
    int m_bScore; /**< Score for the BLACK player. */

    int m_row; /**< Row index for the current move. */
    int m_col; /**< Column index for the current move. */

    eStates** m_pBoard; /**< 2D array representing the game board. */

    /**
     * @brief Checks if the given row and column are out of bounds.
     * @param row The row index.
     * @param col The column index.
     * @return True if out of bounds, false otherwise.
     */
    bool isOutOfBounds(int row, int col) const;

    /**
     * @brief Checks the neighbors of each board position and marks possible moves.
     */
    void checkNeighbors();

    /**
     * @brief Checks if the current move is legal.
     * @return True if legal, false otherwise.
     */
    bool isLegalMove();

    /**
     * @brief Sets the current player's piece on the board and flips pieces accordingly.
     */
    void setPiece();

    /**
     * @brief Flips pieces in all directions based on the current move.
     */
    void flip();

    /**
     * @brief Switches the current player.
     */
    void switchPlayer();

    /**
     * @brief Resets the board by clearing POSSIBLE markers.
     */
    void resetBoard();

    //void checknumofPieces();
};
#endif /* CREVERSIBOARD_H_ */
