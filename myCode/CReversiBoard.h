#ifndef CREVERSIBOARD_H_
#define CREVERSIBOARD_H_

class CReversiBoard {
private:
    enum States {
        EMPTY,
        WHITE,
        BLACK,
        POSSIBLE
    };

    const int NOROWS = 8;
    const int NOCOLS = 8;

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
