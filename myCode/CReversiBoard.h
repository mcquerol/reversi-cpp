#ifndef CREVERSIBOARD_H_
#define CREVERSIBOARD_H_


#define NO_ROWS 8
#define NO_COLS 8
#define OUT_OF_BOUNDS(row, col) (row < 1 && row > NO_ROWS && col < 1 && col > NO_COLS)

class CReversiBoard {
private:
    enum States {
        EMPTY,
        WHITE,
        BLACK,
        POSSIBLE
    };

    int currPlayer;
    int wScore;
    int bScore;

    int** board;

    void checkNeighbors();
    bool isLegalMove(int row, int col);
    void setPiece(int currPlayer, int row, int col);
    void flip(int row, int col);

    void switchPlayer();
    void resetBoard();

public:
    CReversiBoard();
    ~CReversiBoard();

    void play();
    int isGameOver();
};

#endif /* CREVERSIBOARD_H_ */
