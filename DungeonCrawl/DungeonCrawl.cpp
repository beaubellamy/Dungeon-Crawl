// DungeonCrawl.cpp : Defines the entry point for the console application.
//

/*
http://www.cplusplus.com/forum/articles/12974/

https://cppgo.wordpress.com/2014/02/01/simple-dungeon-crawl/

Make a program that outputs a simple grid based gameboard to the screen using 
either numbers or characters.
i.e.

. . . . . . . . . .
.G . . . . . . . .
. . . . ..T . . .
. . . . . . . . . .
. . ..T . . . . .
. . . . ..T . . .
. . . . . . . ..X


or

0 0 0 0 0 0 0 0 0 0
0 5 0 0 6 0 0 0 0 0
0 0 0 0 0 0 7 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 7 0 0 0 0 0 0
0 0 0 0 0 0 7 0 0 0
0 0 0 0 0 0 0 0 0 4


Allow the user(marked by G in the example) to move either up, down, left, or right 
each turn. If the player steps on a trap then they lose.If they make it to the 
treasure 'X' then they win.

- Add enemies that move randomly in any direction once per turn. 
(enemies just like traps cause the player to lose if touched)


*/

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

const int rowSize = 10;
const int colSize = 10;
char board[rowSize][colSize];
int targetRow, targetCol;

void initialiseBoard(int numberOfTraps);
void displayBoard();
bool playerMove(char direction);
int validateIndex(int index, int size);
bool checkWinner(int currentRow, int currentCol);

int main()
{
	char direction;
	bool isWinner;

	int numberOfTraps;
	
	cout << "Enter the number of traps to include. (Must be greater than 0) " << endl;
	cin >> numberOfTraps;
	if (numberOfTraps <= 0)
		numberOfTraps = 3;
	
	/* Initialise the playing board. */
	initialiseBoard(numberOfTraps);
	displayBoard();
	
	isWinner = false;

	while (!isWinner)
	{
		/* Get the players move. */
		cout << "Press 'x' or 'q' to exit. " << endl;
		cout << "up (w) / down (z) left (a) / right (s): " << endl;
		cin >> direction;

		/* Move the player and check if they win. */
		isWinner = playerMove(direction);
		
		/* Check if the game has ended. */
		if (direction == 'x' || direction == 'q')
		{
			cout << "You have exited the game." << endl;
			isWinner = true;
		}

		/* Display the next move. */
		displayBoard();
	} 

	system("pause");
	return 0;
}

/* Initialise the playing board. */
void initialiseBoard(int numberOfTraps)
{

	int trapRow;
	int trapCol;
	targetRow = 0;
	targetCol = 0;

	/* Cycle through the board. */
	for (int row = 0; row < rowSize; row++)
		for (int col = 0; col < colSize; col++)
			board[row][col] = '.';

	/* Set the random seed. */
	srand(time(0));

	/* Set each trap location. */
	for (int i = 0; i < numberOfTraps; i++)
	{
		trapRow = 0;
		trapCol = 0;

		while (trapRow + trapCol == 0)
		{
			trapRow = rand() % rowSize;
			trapCol = rand() % colSize;
			board[trapRow][trapCol] = 'T';
		}
	}

	/* Set the target location. */
	while (targetRow + targetCol == 0)
	{
		targetRow = rand() % rowSize;
		targetCol = rand() % colSize;
	}
	board[targetRow][targetCol] = 'X';

	/* Set the initial player position. */
	board[0][0] = 'G';

}

/* Display the current state of the playing board. */
void displayBoard()
{
	for (int row = 0; row < rowSize; row++)
	{
		for (int col = 0; col < colSize; col++)
			cout << board[row][col] << ' ';
		cout << endl;
	}
}

/* Move the player position, and check for valitity and the end of the game. */
bool playerMove(char direction)
{
	int currentRow, currentCol;

	/* Cycle through the board to find the current player position. */
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			/* Get the current player position. */
			if (board[i][j] == 'G')
			{
				currentRow = i;
				currentCol = j;

				/* Replace current position with standard board peice. */
				board[i][j] = '.';
			}
		}
	}

	/* Move the player */
	switch (direction) {
	case 'w':	// Up
		currentRow--;
		break;
	case 'z':	// Down
		currentRow++;
		break;
	case 'a':	// Left
		currentCol--;
		break;
	case 's':	// Right
		currentCol++;
		break;
	default:
		cout << "Press 'x' or 'q' to exit. " << endl;	
		cout << "Invalid move; select (w) UP; (a) DOWN; (s) RIGHT; (z) LEFT." << endl;
	}
	
	/* Validate the player move remains on the board. */
	currentRow = validateIndex(currentRow, rowSize);
	currentCol = validateIndex(currentCol, colSize);

	/* Check if the player moves on to a trap. */
	if (board[currentRow][currentCol] == 'T')
	{
		cout << "You fell into my trap. YOU LOSE. " << endl;
		return true;
	}

	/* Check if the player finds the target/treasure. */
	if (checkWinner(currentRow, currentCol))
		return true;

	/* Set the player position. */
	board[currentRow][currentCol] = 'G';
	
	return false;
}

/* If the player moves off the board; switch to the other side. */
int validateIndex(int index, int size)
{
	if (index < 0)
		index = size-1;
	if (index >= size)
		index = 0;

	return index;
}

/* Check if the player finds the target/treasure. */
bool checkWinner(int currentRow, int currentCol)
{
	if (currentRow == targetRow && currentCol == targetCol)
	{
		cout << "YOU WIN!" << endl;
		/* Player win's.*/
		return true;
	}

	/* Player hasn't found the target/treasure yet. */
	return false;

}

