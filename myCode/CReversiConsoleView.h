/*
 * CReversiConsoleView.h
 *
 *  Created on: 8 Nov 2021
 *      Author: Mateo C. Querol
 */

#ifndef CREVERSICONSOLEVIEW_H_
#define CREVERSICONSOLEVIEW_H_
#include <iostream>

class CReversiConsoleView
{

private:
	int **boardptr;
public:

	/*
	 * Constructor of this class takes the double pointer from the CReversiBoard class and
	 */
	CReversiConsoleView(int **board);
	~CReversiConsoleView();

	/** print()
	 *
	 * print the board pass from the CReversiBoard class with each player's score
	 */
	void print(std::string playerStr, int wScore, int bScore);
};

#endif /* CREVERSICONSOLEVIEW_H_ */
