#pragma once
#include "Board.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <Windows.h>
using namespace std;
class Board;
class Game
{

	friend class Board;
	Board* board = nullptr;
	Player players[3][5];
	int numberOfPlayers[3]{ 0 };
	int time = 0;
public:
	void displayOpening();
	void play(int);
	void displayMenu();
	void controlSelection();
};

