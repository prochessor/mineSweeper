#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Block.h"
#include "NumberedBlock.h"
#include "MineBlock.h"
#include <conio.h>
#include <Windows.h>
#include <fstream>
using namespace std;
int main()
{
	Game game;
	game.displayMenu();
	_getch();
}