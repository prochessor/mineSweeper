#include "Block.h"
#include "help.h"
void Block::print()
{
		if (isDark)
		{
			myRects(x, y, x + 45, y + 45, 162, 209, 72);

		}
		else
		{
			myRects(x, y, x + 45, y + 45, 132, 204, 50);
		}
	
}
void Block::toggleFlagValue(int& flag)
{
	bool check = false;
	if (flag == 0)
		check = true;
	int x1 = x + 16;
	int y1 = y + 6;
	int x2 = x + 16;
	int y2 = y - 6;
	int r=255, g = 0, b = 0;

	if (isFlaged != true)
	{
		
		if (check == false)
		{
			isFlaged = true;
			flag--;
		}
		
	}
	else
	{
		if (isDark) {
			r = 162;
			g = 209;
			b = 72;
		}
		else {
			r = 132; g = 204, b = 50;
		}
		isFlaged = false;
		flag++;
		check = false;
	}
	if (check == false)
	{

		myLineL(x1, y1, x2, y2 + z - 3, r, g, b, 5);
		myLineL(x1, y1, x2 + 12, y1 + 10, r, g, b, 5);
		myLineL(x1 + 2, y1 + 5, x2 + 8, y1 + 10, r, g, b, 9);
		myLineL(x1 + 8, y1 + 7, x2, y1 + 17, r, g, b, 5);
		myLineL(x1 + 12, y1 + 10, x2, y1 + 17, r, g, b, 5);
		myLineL(x1 - 6, y2 + z - 3, x1 + 8, y2 + z - 3, r, g, b, 5);
	
	}
}
void Block::setAttributes(int x, int y, int z,int h)
{
	{
		this->x = x;
		this->y = y;
		this->z = z;
		isFlaged = false;
		isExposed = false;
		if (h % 2 == 0)
			isDark = true;
		else
			isDark = false;
	}
}
bool Block::compareValues(int x, int y)
{
	if (x >= this->x && x <= this->x + z && y >= this->y && y <= this->y + z)
		return true;
	return false;
}