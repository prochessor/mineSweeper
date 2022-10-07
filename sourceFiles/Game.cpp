#include "Game.h"
#include "Board.h"
#include "Block.h"
#include "help.h"
#include<thread>
#include <Windows.h>
using namespace std;
bool bot= false;
void Game::displayMenu()
{
	GetAsyncKeyState(IGNORE);
	int x = 680;
	int y = 351;
	int r, c;
	gotoxy(26, 6);
	cout << " PLAY GAME" << endl;
	gotoxy(26, 8);
	cout << "INSTRUCTION" << endl;
	gotoxy(26,12);
	cout << "   Exit" << endl;
	gotoxy(26,10);
	cout << "PLAY vs BOT" << endl;
	

	while (1) {
		displayOpening();
		y = 351;
		myRectL(x, y, x + 400, y + 80, 30, 100, 50,6);
		y += 123;
		myRectL(x, y, x + 400, y + 80, 30, 100, 50, 6);
		y += 123;
		myRectL(x, y, x + 400, y + 80, 30, 100, 50, 6);
		y += 123;
		myRectL(x, y, x + 400, y + 75, 30, 100, 50, 6);
		y += 123;
		y = 351;

		if (GetAsyncKeyState(VK_LBUTTON)&0x8000)
		{
			POINT p;
			HWND hwnd = GetConsoleWindow();
			GetCursorPos(&p);

			if (ScreenToClient(hwnd, &p))
			{
				c = p.x * 1.5 + 2;
				r = p.y * 1.5 + 2;
			}
			if (c >= 680 &&c<=1080)
			{
				if (r >= y && r <= y+80)
				{
					controlSelection();
					break;
				}
				if (r >= y + (123 * 1) && r <= y+80 + (123 * 1))
				{
					gotoxy(0, 0);
					system("cls");

					cout << "1. Winnner will be in case of revealing all the block without any \n  mine" << endl;
					cout << "2. To put flag click on the right mouse button" << endl;
					cout << "3. In order to reveal a block press left click of the mouse button" << endl;
					cout << "4. In order to remove the flag that you just placed then right click\n on that flag again" << endl;
					cout << "5. There are 9 mines in easy ,40 mines in medium and 99 mines in hard\n  mode" << endl;
					cout << "6. Be cautious on your every step some of them could be fatal" << endl;
					cout << "7.			\nPRESS ENTER TO RETURN TO THE MAIN MENU" << endl;
					while (1)
					{
						if (GetAsyncKeyState(13))
						{
							system("cls");
							displayMenu();
						}
					}
				}

				if (r >= y + (123 * 2) && r <= y + 80 + (123 * 2))
				{
					bot = true;
					controlSelection();

				}

				if (r >= y + (123 * 3) && r <= y + 80 + (123 * 3))
				{
					system("cls");
					exit(0);
				}

				
			}
		}
	}
}
void Game::controlSelection()
{

	system("cls");
	
	int x = 365;
	int y = 290;
	int r, c;
	gotoxy(15, 5);
	cout << " EASY" << endl;
	gotoxy(30, 5);
	cout << "MEDIUM" << endl;
	gotoxy(45, 5);
	cout << " HARD" << endl;
	

	while (1) {

		x = 365;
		myRectL(x, y, x + 280, y + 80, 30, 100, 50, 6);
		x += 410;
		myRectL(x, y, x + 300, y + 80, 30, 100, 50, 6);
		x += 420;
		myRectL(x, y, x + 300, y + 80, 30, 100, 50, 6);
		if (GetAsyncKeyState(VK_LBUTTON)&1)
		{
			POINT p;
			HWND hwnd = GetConsoleWindow();
			GetCursorPos(&p);

			if (ScreenToClient(hwnd, &p))
			{
				c = p.x * 1.5 + 2;
				r = p.y * 1.5 + 2;
			}
			if (r >= 290 && r <= 370)
			{
				if (c >= 365 && c <= 365 + 280)
				{
					play(1);
					break;
				}
				if (c >= 365+410 && c <= 365+280+410)
				{
					play(2);
					break;

				}
				if (c >= 365 + 410 + 420 && c <= 365 + 280 + 410 + 420)
				{

					play(3);
					break;

				}

			}
		}
	}
}
void Game::play(int level) 
{
	system("cls");
	if (board != nullptr)
		delete board;

	board = new Board;
		
	if (level == 1)
	{
		board->rows = 9;
		board->cols = 9;
		board->numberOfMines = 10;
		board->blocks = new Block ** [board->rows];
		for (int i = 0; i < board->rows; ++i)
		{
			board->blocks[i] = new Block*[board->cols];
		}
	}
	else if (level == 2)
	{
		board->rows = 16;
		board->cols = 16;
		board->numberOfMines = 40;
		board->blocks = new Block ** [board->rows];
		for (int i = 0; i < board->rows; ++i)
		{
			board->blocks[i] = new Block*[board->cols];
		}
	}
	else if (level == 3)
	{
		board->rows = 16;
		board->cols = 30;
		board->numberOfMines = 99;
		board->blocks = new Block ** [board->rows];
		for (int i = 0; i < board->rows; ++i)
		{
			board->blocks[i] = new Block*[board->cols];
		}
	}
	if (bot == true)
	{
		board->bot();
		bot = false;
	}
	system("cls");
	board->controlMinePlacement();
	//delete board;
	Board* ptr = board;
	board->numberOfPlayers = &numberOfPlayers[level-1];
	board->players = players[level-1];
	thread thread1 = ptr->member1();
	thread thread2 = ptr->member2();
	thread1.join();
	thread2.join();
	ofstream out("leaderBoard.txt");
	for (int j = 0; j < 3; ++j)
	{
		if (j == 0)
		{
			out << "Easy: " << endl;
		}
		else if (j == 1)
		{
			out << "Medium" << endl;
		}
		else
		{
			out << "Hard" << endl;
		}
		for (int i = 0; i < numberOfPlayers[level-1]; ++i)
		{
			out << players[j][i].result << " "<<endl;
		}
	}
	system("cls");
	GetAsyncKeyState(IGNORE);
	displayMenu();
	
}
void Game::displayOpening()
{
	myLineL(100+170, 200-120, 100+170, 350-120, 30, 100, 50, 15);
	myLineL(100+170, 200-120, 170+170, 275-120, 30, 100, 50, 15);
	myLineL(170+170, 275-120, 240+170, 200-120, 30, 100, 50, 15);
	myLineL(240+170, 200-120, 240+170, 350-120, 30, 100, 50, 15);
	myLineL(270+170, 200-120, 270+170, 350-120, 30, 100, 50, 15);
	myLineL(300+170, 200-120, 300+170, 350-120, 30, 100, 50, 15);
	myLineL(300+170, 200-120, 400+170, 350-120, 30, 100, 50, 15);
	myLineL(400+170, 200-120, 400+170, 350-120, 30, 100, 50, 15);
	myLineL(430+170, 200-120, 430+170, 350-120, 30, 100, 50, 15);
	myLineL(430+170, 200-120, 500+170, 200-120, 30, 100, 50, 15);
	myLineL(430+170, 275-120, 500+170, 275-120, 30, 100, 50, 15);
	myLineL(430+170, 350-120, 500+170, 350-120, 30, 100, 50, 15);
	myLineL(550+170, 275-120, 575+170, 275-120, 30, 100, 50, 15); //-//
	myLineL(625+170, 200-120, 700+170, 200-120, 30, 100, 50, 15);
	myLineL(625+170, 200-120, 625+170, 275-120, 30, 100, 50, 15);
	myLineL(625+170, 275-120, 700+170, 275-120, 30, 100, 50, 15);
	myLineL(700+170, 275-120, 700+170, 350-120, 30, 100, 50, 15);
	myLineL(625+170, 350-120, 700+170, 350-120, 30, 100, 50, 15);//s
	myLineL(750+170, 200-120, 750+170, 350-120, 30, 100, 50, 15);
	myLineL(750+170, 350-120, 800+170, 275-120, 30, 100, 50, 15);
	myLineL(800+170, 275-120, 850+170, 350-120, 30, 100, 50, 15);
	myLineL(850+170, 200-120, 850+170, 350-120, 30, 100, 50, 15);
	myLineL(900+170, 200-120, 900+170, 350-120, 30, 100, 50, 15);//e
	myLineL(900+170, 200-120, 950+170, 200-120, 30, 100, 50, 15);//e
	myLineL(900+170, 275-120, 950+170, 275-120, 30, 100, 50, 15);//e
	myLineL(900+170, 350-120, 950+170, 350-120, 30, 100, 50, 15);//e
	myLineL(1000+170, 200-120, 1000+170, 350-120, 30, 100, 50, 15);//e
	myLineL(1000+170, 200-120, 1050+170, 200-120, 30, 100, 50, 15);//e
	myLineL(1000+170, 275-120, 1050+170, 275-120, 30, 100, 50, 15);//e
	myLineL(1000+170, 350-120, 1050+170, 350-120, 30, 100, 50, 15);//e
	myLineL(1100+170, 200-120, 1100+170, 350-120, 30, 100, 50, 15);//p
	myLineL(1100+170, 200-120, 1160+170, 250-120, 30, 100, 50, 15);
	myLineL(1160+170, 250-120, 1100+170, 300-120, 30, 100, 50, 15);
	myLineL(1080+170, 350-120, 1120+170, 350-120, 30, 100, 50, 15);//p
	myLineL(1200+170, 200-120, 1200+170, 350-120, 30, 100, 50, 15);//e
	myLineL(1200+170, 200-120, 1250+170, 200-120, 30, 100, 50, 15);//e
	myLineL(1200+170, 275-120, 1250+170, 275-120, 30, 100, 50, 15);//e
	myLineL(1200+170, 350-120, 1250+170, 350-120, 30, 100, 50, 15);//e
	myLineL(1300+170, 200-120, 1300+170, 350-120, 30, 100, 50, 15);//r
	myLineL(1300+170, 200-120, 1360+170, 250-120, 30, 100, 50, 15);
	myLineL(1360+170, 250-120, 1300+170, 300-120, 30, 100, 50, 15);
	myLineL(1300+170, 300-120, 1360+170, 350-120, 30, 100, 50, 15);
}