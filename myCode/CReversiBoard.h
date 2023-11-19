#ifndef CREVERSIBOARD_H_
#define CREVERSIBOARD_H_


#define NO_ROWS 8
#define NO_COLS 8

#define OUT_OF_BOUNDS(row, col) (row < 1 || row > NOROWS) && (col < 1 || col > NOCOLS)

class CReversiBoard {
private:
    enum States {
        EMPTY,
        WHITE,
        BLACK,
        POSSIBLE
    };


    unsigned int currPlayer;
    unsigned int wScore;
    unsigned int bScore;

    unsigned int** board;

    void checkNeighbors(unsigned int color);
    bool isLegalMove(unsigned int x, unsigned int y);
    void setPiece(unsigned int currPlayer, unsigned int x, unsigned int y);
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
