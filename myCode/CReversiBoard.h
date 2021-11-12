/*
 * CReversiBoard.h
 *
 *  Created on: 7 Nov 2021
 *      Author: Mateo C. Querol
 */

#ifndef CREVERSIBOARD_H_
#define CREVERSIBOARD_H_


class CReversiBoard
{

private:

	/** states
	 *
	 * this enum defines the state of each element
	 * of the board array
	 */
	enum states
	{
		EMPTY,
		WHITE,
		BLACK,
		POSSIBLE
	};

	/** currPlayer
	 *
	 * keeps track of the current player (black or white)
	 */
	unsigned int currPlayer;

	/** wScore
	 *
	 * keeps track of the white player score
	 */
	unsigned int wScore; //score of white player

	/** bScore
	 *
	 * keeps track of the black player score
	 */
	unsigned int bScore; //score of white player

	/** checkNeighbors()
	 *
	 * checks surrounding pieces of non empty elements
	 */
	void checkNeighbors(unsigned int color);

	/** isLegalMove()
	 *
	 * checks if a piece can be placed at the position x, y
	 */
	bool isLegalMove(unsigned int x, unsigned int y);

	/** setPiece()
	 *
	 * places the piece of currPlayer's color at position x, y
	 */
	void setPiece(unsigned int currPlayer, unsigned int x, unsigned int y);

	/** flipLine
	 *
	 * flips one piece of the opposite player's color given an x,y (r,c) coordinate with delta constants (direction of travel)
	 * (called recursively)
	 */
	bool flipLine(unsigned int dr, unsigned int dc, unsigned int r, unsigned int c, unsigned int currPlayer);

	/** flip()
	 *
	 * flips one line at a time (above method) given x y as the starting point and direction constants
	 * up, left, right, down, top-left, bottom-left, top-right, bottom-right
	 */
	void flip(unsigned int x, unsigned int y);

	/** switchPlayer()
	 *
	 * switches the current player
	 */
	void switchPlayer();

	/** resetBoard()
	 *
	 * clear all the POSSIBLE elements on the board to switch player prespective
	 */
	void resetBoard();

public:

	/**
	 * Constructor
	 */
	CReversiBoard();

	/**
	 * Destructor
	 */
	~CReversiBoard();

	/**
	 * 2d board of size 8x8
	 */
	unsigned int** board;

	/** play()
	 *
	 * this methods executes all the methods for one player to make a move
	 * and switch player, this is in the superloop in main.cpp
	 */
	void play();

	/** isGameOver()
	 *
	 * this method is called after the play() method in main,
	 * it checks if either player won the game or if the game should continue
	 */
	int isGameOver();

};

#endif /* CREVERSIBOARD_H_ */
