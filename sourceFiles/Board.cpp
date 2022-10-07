#include "Board.h"5
#include "MineBlock.h"
#include <vector>
#include "help.h"
#include "NumberedBlock.h"
#include <Windows.h>
#include <time.h>
#include <string>
#include <string.h>
using namespace std;

void Board::controlMinePlacement()
{
	vector<int> rowValues;
	vector<int> colValues;
	if (firstClick==1)
	{
		bool flag = false;
		if (firstClickRow == 0 || firstClickCol == 0)
			flag = true;
		for (int i = firstClickRow - 1; i < firstClickRow + 2 || flag == true; ++i)
		{
			if (i == firstClickRow + 2)
				break;
			for (int j = firstClickCol - 1; j < firstClickCol + 2 || flag == true; ++j)
			{
				if (j == firstClickCol  + 2)
					break;
				if (i >= 0 && i < rows && j < cols && j >= 0)
				{
					rowValues.push_back(i);
					colValues.push_back(j);
				}

			}
		}
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
		blocks = new Block **[rows];
		for (int i = 0; i < rows; ++i)
		{
			blocks[i] = new Block * [cols];
		}
		
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			
			blocks[i][j] = new NumberedBlock;
		}
	}
	
	srand(time(0));
	for (int i = 0; i < numberOfMines; ++i)
	{
		generateRandom:
		int r = rand()%rows;
		int c = rand()%cols;
		for (int j = 0; j < rowValues.size(); ++j)
		{
			if (rowValues[j] == r && colValues[j] == c)
			{
				
				goto generateRandom;
			}
		}
		delete blocks[r][c];
		blocks[r][c] = new MineBlock;
		rowValues.push_back(r);
		colValues.push_back(c);

	}
	rowValues.clear();
	colValues.clear();
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (blocks[i][j]->type == "MineBlock")
			{
				rowValues.push_back(i);
				colValues.push_back(j);
			}
		}
	}
	for (int i = 0; i < rowValues.size(); ++i)
	{
		int r = rowValues[i];
		int c = colValues[i];
		
		bool flag = false;
		if (r == 0 || c == 0)
			flag = true;
		for (int i = r - 1; i >= 0 && i < rows && i < r + 2 || flag == true; ++i)
		{
			if (i == r + 2)
				break;
			for (int j = c - 1; j >= 0 && j < cols && j < c + 2 || flag == true; ++j)
			{
				if (j == c + 2)
					break;

				if (i >= 0 && i < rows && j >= 0 && j < cols && blocks[i][j]->type!="MineBlock") {
					blocks[i][j]->increaseN();
				}

			}
		}
	}
	if (firstClick == 1 )
	{
		
		firstClick = 2;
	}
	

	int x = 500;
	int y = 50;
	if (rows == 9 && cols == 9)
	{
		x = 900;
		y = 180;
	}
	else if (rows == 16 && cols == 16)
	{
		x = 750;
	}
	for (int i = 0,h=0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j,h++)
		{
			blocks[i][j]->setAttributes(x + 45 * j, y + 45 * i, 45,h);
		}
		if (rows > 9)
		{
			h++;
		}
	}
	printBoard();

}
void Board::printBoard()
{
	int x = blocks[0][0]->x;
	int y = blocks[0][0]->y;
	int x1 = blocks[rows - 1][cols - 1]->x+blocks[rows-1][cols-1]->z;
	int y1 = blocks[rows - 1][cols - 1]->y + blocks[rows - 1][cols - 1]->z;
	myRectL(x-3, y-3, x1+3 ,y1+3, 10, 120, 50,6);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			blocks[i][j]->print();
		}
	}
}
vector<int>loadRows;
vector<int>loadCols;
void Board::expand(int row, int col)
{
	if (blocks[row][col]->isFlaged == true)
		return;
	blocks[row][col]->isExposed = true;
	blocks[row][col]->print();
	if (blocks[row][col]->type == "EmptyBlock")
	{
		bool flag = false;
		if (row == 0 || col == 0)
			flag = true;
		for (int i = row - 1; i >= 0 && i < rows && i < row + 2 || flag == true; ++i)
		{
			if (i == row + 2)
				break;
			for (int j = col - 1; j >= 0 && j < cols && j < col + 2 || flag == true; ++j)
			{
				if (j == col + 2)
					break;
			
				else if ( i >= 0 && i < rows && j >= 0 && j < cols)
				{
					if (blocks[i][j]->isExposed == false)
						expand(i, j);
				}
			}
		}
	}
	else
	{
		loadRows.push_back(row);
		loadCols.push_back(col);
	}
	
}
void Board::bot()
{
	controlMinePlacement();
	firstClick = 1;
	firstClickCol = rand() % cols;
	firstClickRow = rand() % rows;
	controlMinePlacement();
	loadCols.clear();
	loadRows.clear();
	expand(firstClickRow, firstClickCol);
	for (int a = 0; a < loadCols.size(); ++a)
	{

		int i = loadRows[a], j = loadCols[a];
		int r = blocks[i][j]->y - 2, c = blocks[i][j]->x - 2, size = blocks[i][j]->z + 2;

		if (i - 1 >= 0 && blocks[i - 1][j]->isExposed == false)
		{
			myLineN(c, r, c + size, r, 10, 120, 50);
		}
		else if (i - 1 >= 0)
		{
			blocks[i - 1][j]->print();

		}
		if (i + 1 < rows && blocks[i + 1][j]->isExposed == false)
		{
			myLineN(c, r + size, c + size, r + size, 10, 120, 50);
		}
		else if (i + 1 < rows)
		{
			blocks[i + 1][j]->print();

		}
		if (j + 1 < cols && blocks[i][j + 1]->isExposed == false)
		{
			myLineN(c + size, r, c + size, r + size, 10, 120, 50);
		}
		else if (j + 1 < cols)
		{
			blocks[i][j + 1]->print();

		}
		if (j - 1 >= 0 && blocks[i][j - 1]->isExposed == false)
		{
			myLineN(c, r, c, r + size, 10, 120, 50);
		}
		else if (j - 1 >= 0)
		{
			blocks[i][j - 1]->print();

		}
		blocks[i][j]->print();
	}
	for (int a = 0; a < rows; ++a)
	{
		for (int b = 0; b < cols; ++b)
		{
			if (blocks[a][b]->isExposed == true && blocks[a][b]->type == "NumberedBlock")
			{
				blocks[a][b]->print();
			}
		}
	}
	//This puts the flag on every block that is confirm to be mine
flagKaro:

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (blocks[i][j]->type == "NumberedBlock" && blocks[i][j]->isExposed == true)
			{
				int noabuc = 0;
				bool flag = false;
				int	r = i;
				int c = j;
				vector<int> rValues, cValues;
				if (r == 0 || c == 0)
					flag = true;
				for (int a = r - 1; a < r + 2 || flag == true; ++a)
				{
					if (a == r + 2)
						break;
					for (int b = c - 1;b < c + 2 || flag == true; ++b)
					{
						if (b == c + 2)
							break;

						if (a >= 0 && a < rows && b >= 0 && b < cols && blocks[a][b]->isExposed == false) {
							noabuc++;
							rValues.push_back(a);
							cValues.push_back(b);
						}

					}
				}
				if (noabuc == blocks[i][j]->getN())
				{
					for (int k = 0; k < rValues.size(); ++k)
					{
						if(blocks[rValues[k]][cValues[k]]->isFlaged==false)
							blocks[rValues[k]][cValues[k]]->toggleFlagValue(numberOfMines);
						Sleep(10);
					}
				}
			}
		}
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (blocks[i][j]->type == "NumberedBlock" && blocks[i][j]->isExposed == true)
			{
				int noabuc = 0;
				int nofabuc = 0;
				bool flag = false;
				int	r = i;
				int c = j;
				vector<int> rValues, cValues;
				if (r == 0 || c == 0)
					flag = true;
				for (int a = r - 1; a < r + 2 || flag == true; ++a)
				{
					if (a == r + 2)
						break;
					for (int b = c - 1; b < c + 2 || flag == true; ++b)
					{
						if (b == c + 2)
							break;

						if (a >= 0 && a < rows && b >= 0 && b < cols && blocks[a][b]->isExposed == false) {
							noabuc++;
							rValues.push_back(a);
							cValues.push_back(b);
							if (blocks[a][b]->isFlaged == true)
							{
								nofabuc++;
							}
						}
						
						

					}
				}
				if ( nofabuc == blocks[i][j]->getN())
				{

					for (int k = 0; k < rValues.size(); ++k)
					{
						if (blocks[rValues[k]][cValues[k]]->isFlaged == false && blocks[rValues[k]][cValues[k]]->isExposed == false)
						{
							loadCols.clear();
							loadRows.clear();
							expand(rValues[k], cValues[k]);
							for (int a = 0; a < loadCols.size(); ++a)
							{

								int i = loadRows[a], j = loadCols[a];
								int r = blocks[i][j]->y - 2, c = blocks[i][j]->x - 2, size = blocks[i][j]->z + 2;

								if (i - 1 >= 0 && blocks[i - 1][j]->isExposed == false)
								{
									myLineN(c, r, c + size, r, 10, 120, 50);
								}
								else if (i - 1 >= 0)
								{
									blocks[i - 1][j]->print();

								}
								if (i + 1 < rows && blocks[i + 1][j]->isExposed == false)
								{
									myLineN(c, r + size, c + size, r + size, 10, 120, 50);
								}
								else if (i + 1 < rows)
								{
									blocks[i + 1][j]->print();

								}
								if (j + 1 < cols && blocks[i][j + 1]->isExposed == false)
								{
									myLineN(c + size, r, c + size, r + size, 10, 120, 50);
								}
								else if (j + 1 < cols)
								{
									blocks[i][j + 1]->print();

								}
								if (j - 1 >= 0 && blocks[i][j - 1]->isExposed == false)
								{
									myLineN(c, r, c, r + size, 10, 120, 50);
								}
								else if (j - 1 >= 0)
								{
									blocks[i][j - 1]->print();

								}
								blocks[i][j]->print();
							}
							for (int a = 0; a < rows; ++a)
							{
								for (int b = 0; b < cols; ++b)
								{
									if (blocks[a][b]->isExposed == true && blocks[a][b]->type == "NumberedBlock")
									{
										blocks[a][b]->print();
									}
								}
							}
							Sleep(10);

							goto flagKaro;
						}
					}

				}
			}
		}
	}

	goto flagKaro;
}
bool Board::checkIfWinner()
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (blocks[i][j]->type == "NumberedBlock" && blocks[i][j]->isExposed == false)
				return false;
		}
	}
	return true;
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void printNum(int x,int y, int n)
{
	if (n == 1) {
		myLineL(x + 22*2.7, y + 8*2.7, x + 22*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 15*2.7, y + 15*2.7, x + 22*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
	}
	else if (n == 2) {
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 8*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 12*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
	}
	else if (n == 3) {
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 8*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 20*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 14*2.7, y + 20*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);

	}
	else if (n == 4)
	{
		x += 4;
		myLineL(x + 22*2.7, y + 8*2.7, x + 22*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 10*2.7, y + 25*2.7, x + 10*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 25*2.7, x + 30*2.7, y + 25*2.7, 20,140,20, 8);
		x -= 4;
	}
	else if (n == 5)
	{
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 8*2.7, x + 12*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 20*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
	}

	else if (n == 6)
	{
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 8*2.7, x + 12*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 12*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 20*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);

	}

	else if (n == 7)
	{
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 8*2.7, x + 18*2.7, y + 32*2.7, 20,140,20, 8);

	}

	else if (n == 8)
	{
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 8*2.7, x + 12*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 12*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 20*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 8*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
	}
	else if (n == 0)
	{
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 8*2.7, x + 12*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 12*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 20*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 8*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
	}
	else if (n == 9)
	{
		myLineL(x + 12*2.7, y + 8*2.7, x + 30*2.7, y + 8*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 32*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 8*2.7, x + 12*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 20*2.7, x + 30*2.7, y + 32*2.7, 20,140,20, 8);
		myLineL(x + 30*2.7, y + 8*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
		myLineL(x + 12*2.7, y + 20*2.7, x + 30*2.7, y + 20*2.7, 20,140,20, 8);
	}
}
void Board::controlSideBar()
{
	myRectL(100, 52, 450, 760, 0, 139, 0, 20);
	myLineL(100, 400, 445, 400, 0, 139, 0, 20);
	myEllipseS(210, 78, 320, 188, 255,10, 0);
	myEllipseS(257, 125, 272, 140, 255,100, 0);
	myLineL(264, 126, 264, 88, 255,100, 0, 5);
	myLineL(264+5, 133+2, 306, 148, 255,100, 0, 5);
	myLineL(200 + 70, 200 + 220, 200 + 70, 350 + 180, 30, 100, 50, 15);//p

	myLineL(200 + 70, 200 + 220, 240 + 70, 230 + 220, 30, 100, 50, 15);
	myLineL(240 + 70, 230 + 220, 200 + 70, 280 + 220, 30, 100, 50, 15);

	myLineL(180 + 70, 350 + 180, 220 + 70, 350 + 180, 30, 100, 50, 15);//p
	for (int i = 0; stopTimer==false ; ++i)
	{
		printNum(95, 230, minutes1);
		printNum(165, 230, minutes0);
		printNum(260, 230, seconds1);
		printNum(330, 230, seconds0);
		int num = numberOfMines;
		int x = 265;
		myEllipseS(264, 117 + 150, 273, 132 + 148, 20, 140, 20);
		myEllipseS(264, 117 + 180, 273, 132 + 178, 20, 140, 20);
		while (num != 0)
		{
			printNum(x, 580, num % 10);
			num /= 10;
			x -= 80;
		}
		if(numberOfMines<10)
			printNum(x, 580, 0);
		if (numberOfMines == 0)
		{
			x -= 80;
			printNum(x, 580, 0);
		}

		if (startTimer == true)
		{
			seconds++;
			seconds0++;
			if (seconds0 == 10)
			{
				seconds0 = 0;
				seconds1++;
			}
			if (seconds1 == 6)
			{
				seconds1 = 0;
				seconds0 = 0;
				minutes0++;
			}
			if (minutes0 == 10)
			{
				minutes1++;
				minutes0 = 0;
			}
		}
		int y = 200;
		Sleep(1000);
		myRects(111, y, 439, y + 120, 204,204,204);
		myRects(150, 550, 439, 550 + 120, 204, 204, 204);
	}

}
void Board::controlGameOver()
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (blocks[i][j]->type == "MineBlock")
			{
				blocks[i][j]->isExposed = true;
				blocks[i][j]->print();
			}
		}
	}
}
void Board::takeLeftInput()
{
	int x, y;
	int whichbtn;
	while (checkIfWinner() == false)
	{
		getRowColbyLeftClick(x, y, whichbtn);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				if (blocks[i][j]->compareValues(y, x))
				{
					
					if (firstClick == 0 && whichbtn==1)
					{

						firstClick = 1;
						firstClickCol = j;
						firstClickRow = i;
						controlMinePlacement();
						startTimer = true;
					}
					else if (blocks[i][j]->type == "MineBlock"&& whichbtn==1 && blocks[i][j]->isFlaged == false)
					{
						stopTimer = true;
						controlGameOver();
						Sleep(1000);
						int xt = blocks[0][0]->x;
						int yt = blocks[0][0]->y;
						int x1t = blocks[rows - 1][cols - 1]->x + blocks[rows - 1][cols - 1]->z;
						int y1t = blocks[rows - 1][cols - 1]->y + blocks[rows - 1][cols - 1]->z;
						myRects(xt - 5, yt - 5, x1t + 5, y1t + 5, 204, 204, 204);
						for (int i = 0; i < 4; ++i)
						{
							myRects(500, 190, 1500, 1000, 204, 204, 204);
							Sleep(150);
							over();
							Sleep(750);

						}
						
						return;
					}
					if (whichbtn == 1 && blocks[i][j]->isFlaged==false)
					{
						loadCols.clear();
						loadRows.clear();
						expand(i, j);
						for (int a = 0; a < loadCols.size(); ++a)
						{

							int i = loadRows[a], j = loadCols[a];
							int r = blocks[i][j]->y - 2, c = blocks[i][j]->x - 2, size = blocks[i][j]->z + 2;

							if (i - 1 >= 0 && blocks[i - 1][j]->isExposed == false)
							{
								myLineN(c, r, c + size, r, 10, 120, 50);
							}
							else if (i - 1 >= 0)
							{
								blocks[i - 1][j]->print();

							}
							if (i + 1 < rows && blocks[i + 1][j]->isExposed == false)
							{
								myLineN(c, r + size, c + size, r + size, 10, 120, 50);
							}
							else if (i + 1 < rows)
							{
								blocks[i + 1][j]->print();

							}
							if (j + 1 < cols && blocks[i][j + 1]->isExposed == false)
							{
								myLineN(c + size, r, c + size, r + size, 10, 120, 50);
							}
							else if (j + 1 < cols)
							{
								blocks[i][j + 1]->print();

							}
							if (j - 1 >= 0 && blocks[i][j - 1]->isExposed == false)
							{
								myLineN(c, r, c, r + size, 10, 120, 50);
							}
							else if (j - 1 >= 0)
							{
								blocks[i][j - 1]->print();

							}
							blocks[i][j]->print();
						}
						
					}
					else if(whichbtn==2 && blocks[i][j]->isExposed==false)
					{
						if(startTimer==true)
							blocks[i][j]->toggleFlagValue(numberOfMines);
					}
					for (int a = 0; a < rows; ++a)
					{
						for (int b = 0; b < cols; ++b)
						{
							if (blocks[a][b]->isExposed == true && blocks[a][b]->type == "NumberedBlock")
							{
								blocks[a][b]->print();
							}
						}
					}
				}
			}
		}
	} 
	
	stopTimer = true;
	int count = 0;  
	Flick:
	int xt = blocks[0][0]->x;
	int yt = blocks[0][0]->y;
	int x1t = blocks[rows - 1][cols - 1]->x + blocks[rows - 1][cols - 1]->z;
	int y1t = blocks[rows - 1][cols - 1]->y + blocks[rows - 1][cols - 1]->z;
	myRects(xt - 5, yt - 5, x1t + 5, y1t + 5, 204,204,204);
	int x1 = 700;
	int y1 = 200;
	int x2 = 770;
	int y2 = 275;
	
	myLineL(x1, y1, x2, y2, 20,140,20, 20);			   //y
	myLineL(x1 + 70, y1 + 75, x2 + 70, y2 - 75, 20,140,20, 20);//y
	myLineL(x1 + 70, y1 + 75, x1 + 70, y2 + 75, 20,140,20, 20);//y
	myEllipseN(x1 + 150, y1, x2 + 210, y2 + 75, 20, 140, 20, 20);//o

	myLineL(x1 + 320, y1, x2 + 250, y2 + 75, 20,140,20, 20);	 //u
	myLineL(x1 + 420, y1, x2 + 350, y2 + 75, 20,140,20, 20);	 //u
	myLineL(x1 + 320, y1 + 150, x2 + 350, y2 + 75, 20,140,20, 20);//u

	myLineL(x1 + 550-530, y1+220, x2 + 480-530, y2 + 75+220, 20,140,20, 20);					  //w
	myLineL(x1 + 550-530, y1+220 + 150, x2 + 530-530, y2+220, 20,140,20, 20);	  //w
	myLineL(x1 + 600-530, y1+220 + 75, x2 + 580-530, y2 + 75+220, 20,140,20, 20);	  //w
	myLineL(x1 + 650-530, y1+220, x2 + 580-530, y2 + 75+220, 20,140,20, 20);      //w

	myEllipseN(x1 + 680-530, y1+220, x2 + 740-530, y2 + 75+220,20,140,20, 20);

	myLineL(x1 + 850-530, y1+220, x2 + 780-530, y2 + 75+220, 20,140,20, 20);
	myLineL(x1 + 850-530, y1+220, x2 + 880-530, y2 + 75+220, 20,140,20, 20);
	myLineL(x1 + 950-530, y1+220, x2 + 880-530, y2 + 75+220, 20,140,20, 20);
	Sleep(750);

	myRects(500,190,1500,1000, 204, 204, 204);

	Sleep(200);
	count++;
	if (count <= 3)
		goto Flick;
	system("cls");
	gotoxy(25, 5);
	if (*numberOfPlayers == 0)
	{
		string name;
		cout << "Enter your name: ";
		cin >> name;
		string result = name + "   " + to_string(minutes1) + to_string(minutes0) + " : " + to_string(seconds1) + to_string(seconds0);
		players[0].result = result;
		players[0].time = seconds;
		*(numberOfPlayers) = *(numberOfPlayers)+1;
	}
	else
	{
		bool flag = true;
		for (int i = 0; i < *numberOfPlayers; ++i)
		{
			if (seconds < players[i].time)
			{

				flag = false;
			}
		}
		if (flag == false||*numberOfPlayers<5)
		{
			int index = *numberOfPlayers;
			if (index == 5)
				index--;
			system("cls");
			gotoxy(25, 5);

			string name;
			cout << "Enter your name: ";
			cin >> name;
			string result = name + "   " + to_string(minutes1) + to_string(minutes0) + " : " + to_string(seconds1) + to_string(seconds0);
			players[index ].result = result;
			players[index ].time = seconds;
			*(numberOfPlayers) = *(numberOfPlayers)+1;
			if (*numberOfPlayers > 5)
				*numberOfPlayers=5;
			for (int i = 0; i < *numberOfPlayers; ++i)
			{
				for (int j = i; j < *numberOfPlayers; ++j)
				{
					if (players[i].time > players[j].time)
					{
						swap(players[i], players[j]);
					}
				}
			}
		}
	}
}


