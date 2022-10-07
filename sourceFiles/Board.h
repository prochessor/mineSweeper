#pragma once
#include "Block.h"
#include <thread>
#include <string>
#include "Player.h"
using namespace std;
class Board
{
	friend class Game;
	//int timer[5];
	Block*** blocks;
	Player* players;
	int* numberOfPlayers;
	int rows, cols,numberOfMines=0;
	int firstClick = 0;
	int firstClickRow, firstClickCol;
	bool startTimer = false;
	int seconds = 0;
	int minutes0 = 0;
	int minutes1 = 0;
	int seconds0 = 0;
	int seconds1 = 0;
	bool stopTimer = false;
	~Board()
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				delete blocks[i][j];
			}
		}
		for (int i = 0; i < rows; ++i)
		{
			delete[] blocks[i];
		}
		delete[] blocks;
		rows = 0;
		cols = 0;
	}
public:
	void controlGameOver();

	void controlMinePlacement();
	void expand(int row, int col);
	void takeLeftInput();
	void printBoard();
	void bot();
	bool checkIfWinner();
	void controlSideBar();
	thread member1() {
		return thread([=] { controlSideBar(); });
	}
	thread member2() {
		return thread([=] { takeLeftInput(); });
	}
};

